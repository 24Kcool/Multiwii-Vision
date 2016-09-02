#ifndef IMU_H_
#define IMU_H_

#define BARO_TAB_SIZE   21

#if BARO
uint8_t getEstimatedAltitude();
#endif

void computeIMU();
int32_t mul(int16_t a, int16_t b);
int32_t _cos10(int16_t x);

#endif /* IMU_H_ */
