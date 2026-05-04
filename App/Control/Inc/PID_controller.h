#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "emc_error.h"

struct PID_controller_s;
typedef struct PID_controller_s *PID_handle;

typedef struct {

  float kp;
  float ki;
  float kd;

  float dt;

  float output_min;
  float output_max;
  float integral_limit;

} PID_config;

/**
 * @brief PID kontrolcüsünü dinamik olarak başlatır ve yapılandırır.
 *
 * @param p_handle Oluşturulan kontrolcüye erişim sağlayacak işaretçi adresi.
 * @param p_config Katsayılar ve limitleri içeren yapılandırma verisi.
 * @return error_t Başarılı ise NO_ERROR, kaynak yetersizse ERR_NO_MEMORY döner.
 */
error_t PID_init(PID_handle *p_handle, const PID_config *p_config);
/**
 * @brief Kontrolcünün iç durumunu (integral toplamı vb.) sıfırlar.
 *
 * @param handle İşlem yapılacak PID nesnesinin tutamacı (handle).
 * @return error_t Handle geçersiz ise ERR_INVALID_PARAM döner.
 */
error_t PID_reset(PID_handle handle);
/**
 * @brief Mevcut bir kontrolcünün parametrelerini çalışma zamanında günceller.
 *
 * @param handle Güncellenecek PID nesnesi.
 * @param p_config Yeni katsayıları içeren yapılandırma işaretçisi.
 * @return error_t Parametreler geçersizse (örn: dt <= 0) hata döner.
 */
error_t PID_reinit(PID_handle handle, const PID_config *p_config);
/**
 * @brief Kontrolcüyü kapatır, belleği serbest bırakır ve işaretçiyi NULL yapar.
 *
 * @param p_handle Serbest bırakılacak handle işaretçisinin adresi.
 * @return error_t Başarılı bir şekilde kapatıldıysa NO_ERROR döner.
 */
error_t PID_deinit(PID_handle *handle);
/**
 * @brief Sabit zaman aralıklarında (dt) çağrılan ana hesaplama döngüsü.
 *
 * @param handle Hesaplama için kullanılacak PID nesnesi.
 * @param setpoint Hedeflenen değer.
 * @param measure Sensörden gelen mevcut ölçüm.
 * @return float Hesaplanan kontrol sinyali çıkışı (u[t]).
 */
float PID_cycle(PID_handle handle, float setpoint, float measure);

#endif
