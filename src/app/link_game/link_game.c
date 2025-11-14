#include "link_game.h"
#include "gui_guider.h"

void link_init_board(uint32_t seed) {
    int total = LINK_ROWS * LINK_COLS;
    int types = total / 2;
    int *vals = (int *)lv_mem_alloc(total * sizeof(int));
    for (int i = 0; i < types; i++) {
        vals[2 * i] = i + 1;
        vals[2 * i + 1] = i + 1;
    }
    unsigned int s = seed ? seed : (unsigned int)lv_tick_get();
    for (int i = 0; i < total; i++) {
        s = s * 1103515245U + 12345U;
        int j = s % total;
        int t = vals[i];
        vals[i] = vals[j];
        vals[j] = t;
    }
    if (!board)
        board = (int *)lv_mem_alloc((LINK_ROWS + 2) * (LINK_COLS + 2) * sizeof(int));
    for (int r = 0; r < LINK_ROWS + 2; r++) {
        for (int c = 0; c < LINK_COLS + 2; c++) {
            BR(r, c) = 0;
        }
    }
    int k = 0;
    for (int r = 1; r <= LINK_ROWS; r++) {
        for (int c = 1; c <= LINK_COLS; c++) {
            BR(r, c) = vals[k++];
        }
    }
    lv_mem_free(vals);
}

static void set_tile_selected(lv_obj_t *obj, bool sel) {
    if (sel) {
        lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(obj, lv_color_hex(0xff5e00), LV_PART_MAIN | LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

static bool link_check_win(void) {
    for (int r = 1; r <= LINK_ROWS; r++) {
        for (int c = 1; c <= LINK_COLS; c++) {
            if (BR(r, c) != 0)
                return false;
        }
    }
    return true;
}

static bool link_can_connect(int r1, int c1, int r2, int c2) {
    int cells = (LINK_ROWS + 2) * (LINK_COLS + 2);
    int *visited = (int *)lv_mem_alloc(cells * 4 * sizeof(int));
    for (int i = 0; i < cells * 4; i++)
        visited[i] = -1;
    int max_states = cells * 4;
    int *qr = (int *)lv_mem_alloc(max_states * sizeof(int));
    int *qc = (int *)lv_mem_alloc(max_states * sizeof(int));
    int *qd = (int *)lv_mem_alloc(max_states * sizeof(int));
    int *qt = (int *)lv_mem_alloc(max_states * sizeof(int));
    int qh = 0, qi = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        visited[(r1 * (LINK_COLS + 2) + c1) * 4 + d] = 0;
        qr[qi] = r1;
        qc[qi] = c1;
        qd[qi] = d;
        qt[qi] = 0;
        qi++;
    }
    while (qh < qi) {
        int r = qr[qh], c = qc[qh], dir = qd[qh], turns = qt[qh];
        qh++;
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        while (nr >= 0 && nr < LINK_ROWS + 2 && nc >= 0 && nc < LINK_COLS + 2) {
            if (nr == r2 && nc == c2)
                return true;
            if (BR(nr, nc) != 0)
                break;
            int vi = (nr * (LINK_COLS + 2) + nc) * 4 + dir;
            if (visited[vi] == -1) {
                visited[vi] = turns;
                qr[qi] = nr;
                qc[qi] = nc;
                qd[qi] = dir;
                qt[qi] = turns;
                qi++;
            }
            nr += dr[dir];
            nc += dc[dir];
        }
        for (int nd = 0; nd < 4; nd++) {
            if (nd == dir)
                continue;
            int nturns = turns + 1;
            if (nturns > LINK_MAX_TURNS)
                continue;
            int ar = r + dr[nd];
            int ac = c + dc[nd];
            while (ar >= 0 && ar < LINK_ROWS + 2 && ac >= 0 && ac < LINK_COLS + 2) {
                if (ar == r2 && ac == c2)
                    return true;
                if (BR(ar, ac) != 0)
                    break;
                int vi2 = (ar * (LINK_COLS + 2) + ac) * 4 + nd;
                if (visited[vi2] == -1 || visited[vi2] > nturns) {
                    visited[vi2] = nturns;
                    qr[qi] = ar;
                    qc[qi] = ac;
                    qd[qi] = nd;
                    qt[qi] = nturns;
                    qi++;
                }
                ar += dr[nd];
                ac += dc[nd];
            }
        }
    }
    lv_mem_free(visited);
    lv_mem_free(qr);
    lv_mem_free(qc);
    lv_mem_free(qd);
    lv_mem_free(qt);
    return false;
}

static void link_remove_tile(int r, int c) {
    BR(r, c) = 0;
    lv_obj_t *obj = TL(r, c);
    if (obj)
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

static void show_win(void) {
    lv_obj_t *label = lv_label_create(link_root);
    lv_label_set_text(label, "胜利！");
    lv_obj_set_style_text_font(label, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

static void tile_event_cb(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    int r = -1, c = -1;
    for (int idx = 0; idx < LINK_ROWS * LINK_COLS; idx++) {
        if (tiles[idx] == obj) {
            r = idx / LINK_COLS + 1;
            c = idx % LINK_COLS + 1;
            break;
        }
    }
    if (r == -1)
        return;
    if (BR(r, c) == 0)
        return;
    if (sel_r == -1) {
        sel_r = r;
        sel_c = c;
        set_tile_selected(obj, true);
        return;
    }
    if (sel_r == r && sel_c == c) {
        set_tile_selected(obj, false);
        sel_r = -1;
        sel_c = -1;
        return;
    }
    lv_obj_t *prev = TL(sel_r, sel_c);
    int v1 = BR(sel_r, sel_c);
    int v2 = BR(r, c);
    if (v1 != v2) {
        set_tile_selected(prev, false);
        set_tile_selected(obj, true);
        sel_r = r;
        sel_c = c;
        return;
    }
    int tmp1 = BR(sel_r, sel_c);
    int tmp2 = BR(r, c);
    BR(sel_r, sel_c) = 0;
    BR(r, c) = 0;
    bool ok = link_can_connect(sel_r, sel_c, r, c);
    BR(sel_r, sel_c) = tmp1;
    BR(r, c) = tmp2;
    if (ok) {
        link_remove_tile(sel_r, sel_c);
        link_remove_tile(r, c);
        set_tile_selected(prev, false);
        sel_r = -1;
        sel_c = -1;
        if (link_check_win())
            show_win();
    } else {
        set_tile_selected(prev, false);
        set_tile_selected(obj, true);
        sel_r = r;
        sel_c = c;
    }
}

void link_create_grid(lv_ui *ui) {
    int tile_w = 44;
    int tile_h = 34;
    grid_container = lv_obj_create(ui->link_game_app);
    lv_obj_set_size(grid_container, LINK_COLS * tile_w, LINK_ROWS * tile_h);
    lv_obj_align(grid_container, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_style_bg_opa(grid_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (!tiles)
        tiles = (lv_obj_t **)lv_mem_alloc(LINK_ROWS * LINK_COLS * sizeof(lv_obj_t *));
    for (int r = 1; r <= LINK_ROWS; r++) {
        for (int c = 1; c <= LINK_COLS; c++) {
            lv_obj_t *btn = lv_btn_create(grid_container);
            tiles[(r - 1) * LINK_COLS + (c - 1)] = btn;
            lv_obj_set_size(btn, tile_w - 6, tile_h - 6);
            lv_obj_set_pos(btn, (c - 1) * tile_w + 3, (r - 1) * tile_h + 3);
            lv_obj_set_style_radius(btn, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            unsigned color_seed = 0x1234u * BR(r, c) + 0x55u;
            lv_color_t col = lv_color_hex(0x003366 ^ (color_seed * 2654435761u));
            lv_obj_set_style_bg_color(btn, col, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(btn, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_t *label = lv_label_create(btn);
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%d", BR(r, c));
            lv_label_set_text(label, buf);
            lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
            lv_obj_add_event_cb(btn, tile_event_cb, LV_EVENT_CLICKED, NULL);
            if (BR(r, c) == 0)
                lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static void link_update_ui(void) {
    for (int r = 1; r <= LINK_ROWS; r++) {
        for (int c = 1; c <= LINK_COLS; c++) {
            lv_obj_t *btn = TL(r, c);
            if (!btn)
                continue;
            unsigned color_seed = 0x1234u * BR(r, c) + 0x55u;
            lv_color_t col = lv_color_hex(0x003366 ^ (color_seed * 2654435761u));
            lv_obj_set_style_bg_color(btn, col, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_t *label = lv_obj_get_child(btn, 0);
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%d", BR(r, c));
            if (label)
                lv_label_set_text(label, buf);
            if (BR(r, c) == 0) {
                lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}

static void link_reset(uint32_t seed) {
    sel_r = -1;
    sel_c = -1;
    link_init_board(seed);
    link_update_ui();
}

void reset_event_cb(lv_event_t *e) {
    uint32_t seed = lv_tick_get();
    link_reset(seed);
}

void root_delete_cb(lv_event_t *e) {
    if (tiles) {
        lv_mem_free(tiles);
        tiles = NULL;
    }
    if (board) {
        lv_mem_free(board);
        board = NULL;
    }
}