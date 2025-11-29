#include "mpu6050_dmp.h"

#include <math.h>
#include <string.h>

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpl_porting.h"

#define DEFAULT_MPU_HZ          100U
#define RAD_TO_DEG              (57.29577951308232f)
#define Q30                      (1073741824.0f)
#define Q30_INV                 (1.0f / Q30)

static uint8_t s_dmp_ready = 0U;
static uint8_t s_has_reference = 0U;
static long s_reference_quat[4] = {0};

/* Identity orientation matrix: adjust if sensor axes differ from board axes. */
static const signed char gyro_orientation[9] = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
};

static unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;

    return b;
}

static unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}

static int dmp_acquire(long *quat, short *gyro, short *accel, unsigned long *timestamp, short *sensors)
{
    if (s_dmp_ready == 0U) {
        return MPU6050_DMP_ERR_INIT;
    }

    short status;
    if (mpu_get_int_status(&status) != 0) {
        return MPU6050_DMP_ERR_STATUS;
    }
    if ((status & MPU_INT_STATUS_DMP) == 0) {
        return MPU6050_DMP_NOT_READY;
    }

    short local_sensors = 0;
    unsigned char more = 0;
    short local_gyro[3];
    short local_accel[3];
    long local_quat[4];
    unsigned long local_timestamp = 0;

    short *gyro_buf = (gyro != NULL) ? gyro : local_gyro;
    short *accel_buf = (accel != NULL) ? accel : local_accel;
    long *quat_buf = (quat != NULL) ? quat : local_quat;
    unsigned long *timestamp_buf = (timestamp != NULL) ? timestamp : &local_timestamp;

    do {
        if (dmp_read_fifo(gyro_buf, accel_buf, quat_buf, timestamp_buf, &local_sensors, &more) != 0) {
            return MPU6050_DMP_ERR_FIFO;
        }
    } while (more != 0U);

    if ((local_sensors & INV_WXYZ_QUAT) == 0) {
        return MPU6050_DMP_ERR_QUAT;
    }

    if (quat != NULL && quat_buf != quat) {
        memcpy(quat, quat_buf, sizeof(long) * 4U);
    }
    if (gyro != NULL && gyro_buf != gyro) {
        memcpy(gyro, gyro_buf, sizeof(short) * 3U);
    }
    if (accel != NULL && accel_buf != accel) {
        memcpy(accel, accel_buf, sizeof(short) * 3U);
    }
    if (sensors != NULL) {
        *sensors = local_sensors;
    }

    return MPU6050_DMP_OK;
}

int mpu6050_dmp_init(void)
{
    if (s_dmp_ready != 0U) {
        return MPU6050_DMP_OK;
    }

    struct int_param_s int_param;
    memset(&int_param, 0, sizeof(int_param));

    if (mpu_init(&int_param) != 0) {
        return MPU6050_DMP_ERR_INIT;
    }

    if (mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_set_sample_rate(DEFAULT_MPU_HZ) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_set_gyro_fsr(2000) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_set_accel_fsr(2) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_set_lpf(42) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (dmp_load_motion_driver_firmware() != 0) {
        return MPU6050_DMP_ERR_INIT;
    }

    if (dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    unsigned short features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO;
    if (dmp_enable_feature(features) != 0) {
        return MPU6050_DMP_ERR_FEATURE;
    }

    if (dmp_set_fifo_rate(DEFAULT_MPU_HZ) != 0) {
        return MPU6050_DMP_ERR_CONFIG;
    }

    if (mpu_set_dmp_state(1) != 0) {
        return MPU6050_DMP_ERR_ENABLE;
    }

    if (mpu_reset_fifo() != 0) {
        return MPU6050_DMP_ERR_FIFO_RESET;
    }

    s_dmp_ready = 1U;
    return MPU6050_DMP_OK;
}

int mpu6050_dmp_read(mpu6050_dmp_data_t *out)
{
    if (out == NULL) {
        return MPU6050_DMP_ERR_FIFO;
    }
    short gyro[3];
    short accel[3];
    long quat[4];
    unsigned long timestamp = 0;
    int ret = dmp_acquire(quat, gyro, accel, &timestamp, NULL);
    if (ret != MPU6050_DMP_OK) {
        return ret;
    }

    memcpy(out->gyro, gyro, sizeof(out->gyro));
    memcpy(out->accel, accel, sizeof(out->accel));
    out->timestamp_ms = timestamp;

    float q_cur[4];
    for (uint8_t i = 0; i < 4U; ++i) {
        q_cur[i] = (float)quat[i] * Q30_INV;
    }

    float q_use[4];
    if (s_has_reference) {
        float q_ref[4];
        for (uint8_t i = 0; i < 4U; ++i) {
            q_ref[i] = (float)s_reference_quat[i] * Q30_INV;
        }
        float q_ref_conj[4] = {q_ref[0], -q_ref[1], -q_ref[2], -q_ref[3]};
        q_use[0] = q_ref_conj[0] * q_cur[0] - q_ref_conj[1] * q_cur[1] - q_ref_conj[2] * q_cur[2] - q_ref_conj[3] * q_cur[3];
        q_use[1] = q_ref_conj[0] * q_cur[1] + q_ref_conj[1] * q_cur[0] + q_ref_conj[2] * q_cur[3] - q_ref_conj[3] * q_cur[2];
        q_use[2] = q_ref_conj[0] * q_cur[2] - q_ref_conj[1] * q_cur[3] + q_ref_conj[2] * q_cur[0] + q_ref_conj[3] * q_cur[1];
        q_use[3] = q_ref_conj[0] * q_cur[3] + q_ref_conj[1] * q_cur[2] - q_ref_conj[2] * q_cur[1] + q_ref_conj[3] * q_cur[0];
    } else {
        for (uint8_t i = 0; i < 4U; ++i) {
            q_use[i] = q_cur[i];
        }
    }

    float norm = sqrtf(q_use[0] * q_use[0] + q_use[1] * q_use[1] + q_use[2] * q_use[2] + q_use[3] * q_use[3]);
    if (norm > 0.0f) {
        for (uint8_t i = 0; i < 4U; ++i) {
            q_use[i] /= norm;
        }
    }

    for (uint8_t i = 0; i < 4U; ++i) {
        out->quat[i] = (long)(q_use[i] * Q30);
    }

    float sinp = -2.0f * (q_use[1] * q_use[3] - q_use[0] * q_use[2]);
    if (sinp > 1.0f) {
        sinp = 1.0f;
    } else if (sinp < -1.0f) {
        sinp = -1.0f;
    }

    out->pitch = asinf(sinp) * RAD_TO_DEG;
    out->roll = atan2f(2.0f * (q_use[2] * q_use[3] + q_use[0] * q_use[1]),
                       1.0f - 2.0f * (q_use[1] * q_use[1] + q_use[2] * q_use[2])) * RAD_TO_DEG;
    out->yaw = atan2f(2.0f * (q_use[1] * q_use[2] + q_use[0] * q_use[3]),
                      1.0f - 2.0f * (q_use[2] * q_use[2] + q_use[3] * q_use[3])) * RAD_TO_DEG;

    return MPU6050_DMP_OK;
}

int mpu6050_dmp_calibrate(void)
{
    if (s_dmp_ready == 0U) {
        return MPU6050_DMP_ERR_INIT;
    }

    long quat[4];
    int ret = MPU6050_DMP_NOT_READY;
    for (uint8_t attempt = 0; attempt < 5U; ++attempt) {
        ret = dmp_acquire(quat, NULL, NULL, NULL, NULL);
        if (ret == MPU6050_DMP_NOT_READY) {
            mpl_delay_ms(5UL);
            continue;
        }
        break;
    }

    if (ret == MPU6050_DMP_OK) {
        memcpy(s_reference_quat, quat, sizeof(s_reference_quat));
        s_has_reference = 1U;
    }

    return ret;
}

void mpu6050_dmp_clear_calibration(void)
{
    s_has_reference = 0U;
    memset(s_reference_quat, 0, sizeof(s_reference_quat));
}
