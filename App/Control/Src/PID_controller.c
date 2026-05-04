#include "PID_controller.h"
#include "emc_error.h"
#include <stdint.h>
#include <string.h>
#define PID_instance_max 5

typedef struct PID_controller_s {

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

static struct PID_controller_s PID_instance[PID_instance_max];
static uint8_t PID_instance_value = 0;

error_t pid_init(PID_handle *p_handle, const PID_config *p_config) {

  if (p_handle == NULL || p_config == NULL) {
    return BAD_PARAMETER;
  }

  if (p_config->dt <= 0.0f || p_config->output_max <= p_config->output_min) {
    return BAD_PARAMETER;
  }

  if ((*p_handle) == NULL) {

    if (PID_instance_value >= PID_instance_max) {
      return LIMIT_EXCEEDED;
    }

    (*p_handle) = &PID_instance[PID_instance_value]; /*  (*p_handle)
                                                        kullanicinin pointeri*/
    PID_instance_value++;
  }

  /* ----------------------------------- */

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
