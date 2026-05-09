#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#include "PID_controller.h"
typedef enum {

  PID_STATE_UNINIT = 0, // Başlangıç durumu
  PID_STATE_IDLE,       // Kurulum yapıldı ama kontrol kapalı
  PID_STATE_RUNNING,    // PID_cycle aktif olarak çalışıyor
  PID_STATE_ERROR       // Kapatılmayı gerektiren bir hata var

} PID_SystemState_t;

typedef enum {

  EVENT_NONE = 0,
  EVENT_START_CMD,
  EVENT_STOP_CMD,
  EVENT_FAULT_DETECTED

} PID_event_t;

typedef struct {

  PID_SystemState_t current_state;
  PID_handle pid_h;
  float output;

} PID_Manager_t;

/**
 * @brief PID Manager katmanını başlatır ve alt seviye PID nesnesini oluşturur.
 * @param config PID katsayıları ve limitlerini içeren yapılandırma seti.
 * @note Bu fonksiyon çağrıldıktan sonra sistem PID_STATE_IDLE durumuna geçer.
 * @return void
 */
void PID_MInit(PID_config *config);

/**
 * @brief Dış dünyadan gelen olaylara göre sistem durumunu günceller.
 *
 * @param event Tetiklenen olay (START, STOP, FAULT vb.).
 * @return void
 */
void PID_MEvent_s(PID_event_t event);

/**
 * @brief PID döngüsünü işleten ana görev fonksiyonu.
 *
 * @details Eğer sistem RUNNING durumundaysa PID_cycle çağrılır.
 *          IDLE veya ERROR durumundaysa güvenli çıkış üretilir.
 *
 * @param current_measure Sensörden gelen anlık geri besleme değeri.
 * @param current_setpoint Hedeflenen değer.
 * @return float Hesaplanan kontrol sinyali (u[t]). Sistem aktif değilse 0.0f
 * döner.
 */
float PID_MTask(float current_measure, float current_setpoint);

#endif
