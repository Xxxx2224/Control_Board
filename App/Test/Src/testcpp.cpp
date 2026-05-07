#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/Utest.h"
#include "CppUTest/UtestMacros.h"
#include "emc_error.h"

extern "C" {
#include "PID_controller.h"
}

TEST_GROUP(pid) {
  PID_config config;
  PID_handle handle;

  void setup() {
    handle = NULL;
    config.kp = 0.1f;
    config.ki = 0.0f;
    config.kd = 0.0f;
    config.dt = 2.0f;
    config.output_min = -100.0f;
    config.output_max = 100.0f;
    config.integral_limit = 50.0f;
  }

  void teardown() {}
};

TEST(pid, pid_test) { CHECK_EQUAL(NO_ERROR, PID_init(&handle, &config)); }
TEST(pid, pid) {
  CHECK_EQUAL(NO_ERROR, PID_init(&handle, &config));

  DOUBLES_EQUAL(1.0f, PID_cycle(handle, 10.0f, 0.0f), 0.001f);
  CHECK_EQUAL(NO_ERROR, PID_reset(handle));
  CHECK_EQUAL(NO_ERROR, PID_deinit(&handle));
  CHECK_EQUAL(NO_ERROR, PID_init(&handle, &config));
  CHECK_EQUAL(NO_ERROR, PID_deinit(&handle));
}

int main(int ac, char **av) {
  return CommandLineTestRunner::RunAllTests(ac, av);
}
