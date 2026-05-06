#include "PID_controller.h"
#include "emc_error.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#define PID_instance_max 5

/* daha sonra guvenlik amacli structlara imza kontrol kisimlari eklenecek */
typedef struct PID_controller_s {
  uint8_t is_active;
  float dt;

  float output_min;
  float output_max;
  float integral_limit;

  float integrator;
  float previous_error;
  float previous_input;

  float kp;
  float kd;
  float ki;

} PID_controller_s;

static struct PID_controller_s PID_instance[PID_instance_max] = {0};
static uint8_t PID_instance_value = 0;

error_t pid_init(PID_handle *p_handle, const PID_config *p_config) {

  if (p_handle == NULL || p_config == NULL || ((*p_handle) != NULL)) {
    return BAD_PARAMETER;
  }

  if (p_config->dt <= 0.0f || p_config->output_max <= p_config->output_min) {
    return BAD_PARAMETER;
  }
  if (PID_instance_value >= PID_instance_max) {
    return LIMIT_EXCEEDED;
  }
  if (PID_instance[PID_instance_value].is_active > 1) {
    /* Buraya birdaha bakilacak */
    return INDEX_OUT_OF_RANGE;
  }
  if (PID_instance[PID_instance_value].is_active != 0) {
    return ILLEGAL_USE_OF_NULL_PTR;
  }

  (*p_handle) = &PID_instance[PID_instance_value]; /*  (*p_handle)
                                                      kullanicinin pointeri*/
  PID_instance_value++;

  /* ----------------------------------- */

  (*p_handle)->is_active = (*p_handle)->is_active + 1;

  (*p_handle)->kp = p_config->kp;

  (*p_handle)->ki = p_config->ki;

  (*p_handle)->kd = p_config->kd;

  (*p_handle)->dt = p_config->dt;

  (*p_handle)->output_max = p_config->output_max;

  (*p_handle)->output_min = p_config->output_min;

  (*p_handle)->integral_limit = p_config->integral_limit;

  (*p_handle)->integrator = 0.0f;

  (*p_handle)->previous_error = 0.0f;

  (*p_handle)->previous_input = 0.0f;

  /* ----------------------------------- */
  /*PID_controller_s havuzunu dairesel bir tampon olarak kullanabilirim birdaha
   * bakacagim*/

  return NO_ERROR;
}

error_t PID_deinit(PID_handle *p_handle) {

  if (p_handle == NULL || (*p_handle) == NULL) {
    return BAD_PARAMETER;
  }
  if ((*p_handle)->is_active > 1) {
    /* Buraya bakilacak */
    return INDEX_OUT_OF_RANGE;
  }

  if ((*p_handle)->is_active == 0) {
    return DOUBLE_FREE;
  }

  /* ----------------------------------- */

  (*p_handle)->kp = 0.0f;

  (*p_handle)->ki = 0.0f;

  (*p_handle)->kd = 0.0f;

  (*p_handle)->dt = 0.0f;

  (*p_handle)->output_max = 0.0f;

  (*p_handle)->output_min = 0.0f;

  (*p_handle)->integral_limit = 0.0f;

  (*p_handle)->integrator = 0.0f;

  (*p_handle)->previous_error = 0.0f;

  (*p_handle)->previous_input = 0.0f;

  (*p_handle)->is_active = (*p_handle)->is_active - 1;

  /* ----------------------------------- */

  (*p_handle) = NULL;

  return NO_ERROR;
}

error_t PID_reset(PID_handle u_handle) {
  if (u_handle == NULL || u_handle->is_active != 1) {
    return BAD_PARAMETER;
  }

  u_handle->integrator = 0.0f;
  u_handle->previous_error = 0.0f;
  u_handle->previous_input = 0.0f;

  return NO_ERROR;
}

error_t PID_reinit(PID_handle u_handle, const PID_config *p_config) {
  if (u_handle == NULL || u_handle->is_active != 1) {
    return BAD_PARAMETER;
  }

  u_handle->kp = p_config->kp;

  u_handle->ki = p_config->ki;

  u_handle->kd = p_config->kd;

  u_handle->dt = p_config->dt;

  u_handle->output_max = p_config->output_max;

  u_handle->output_min = p_config->output_min;

  u_handle->integral_limit = p_config->integral_limit;

  return NO_ERROR;
}

float PID_cycle(PID_handle u_handle, float setpoint, float measure) {
  if (u_handle == NULL) {
    return 0.0f;
  }

  float error = setpoint - measure;
  float p_term = u_handle->kp * error;
  float i_term = u_handle->integrator + (u_handle->ki * error * u_handle->dt);

  float d_term =
      u_handle->kd * (u_handle->previous_input - measure) / u_handle->dt;

  if (i_term > u_handle->integral_limit) {
    i_term = u_handle->integral_limit;
  }

  else if (i_term < -u_handle->integral_limit) {
    i_term = -u_handle->integral_limit;
  }

  float PID_output = p_term + i_term + d_term;

  if (PID_output > u_handle->output_max) {
    PID_output = u_handle->output_max;
  }

  else if (PID_output < u_handle->output_min) {
    PID_output = u_handle->output_min;
  }

  u_handle->integrator = i_term;
  u_handle->previous_input = measure;

  return PID_output;
}
