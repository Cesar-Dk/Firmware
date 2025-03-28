                                      /*!< fCHPFRQ = fHRTIM / 32  */
#define LL_HRTIM_CHP_PRESCALER_DIV48  (HRTIM_CHPR_CARFRQ_1)                                                                    /*!< fCHPFRQ = fHRTIM / 48  */
#define LL_HRTIM_CHP_PRESCALER_DIV64  (HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 64  */
#define LL_HRTIM_CHP_PRESCALER_DIV80  (HRTIM_CHPR_CARFRQ_2)                                                                    /*!< fCHPFRQ = fHRTIM / 80  */
#define LL_HRTIM_CHP_PRESCALER_DIV96  (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 96  */
#define LL_HRTIM_CHP_PRESCALER_DIV112 (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1)                                              /*!< fCHPFRQ = fHRTIM / 112  */
#define LL_HRTIM_CHP_PRESCALER_DIV128 (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 128  */
#define LL_HRTIM_CHP_PRESCALER_DIV144 (HRTIM_CHPR_CARFRQ_3)                                                                    /*!< fCHPFRQ = fHRTIM / 144  */
#define LL_HRTIM_CHP_PRESCALER_DIV160 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 160  */
#define LL_HRTIM_CHP_PRESCALER_DIV176 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_1)                                              /*!< fCHPFRQ = fHRTIM / 176  */
#define LL_HRTIM_CHP_PRESCALER_DIV192 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 192  */
#define LL_HRTIM_CHP_PRESCALER_DIV208 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2)                                              /*!< fCHPFRQ = fHRTIM / 208  */
#define LL_HRTIM_CHP_PRESCALER_DIV224 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 224  */
#define LL_HRTIM_CHP_PRESCALER_DIV240 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1)                        /*!< fCHPFRQ = fHRTIM / 240  */
#define LL_HRTIM_CHP_PRESCALER_DIV256 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)  /*!< fCHPFRQ = fHRTIM / 256  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CHP_DUTYCYCLE CHOPPER MODE DUTY CYCLE
  * @{
  * @brief Constants defining the duty cycle of the generated high frequency carrier. Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8).
  */
#define LL_HRTIM_CHP_DUTYCYCLE_0    0x00000000U                                              /*!< Only 1st pulse is present */
#define LL_HRTIM_CHP_DUTYCYCLE_125  (HRTIM_CHPR_CARDTY_0)                                             /*!< Duty cycle of the carrier signal is 12.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_250  (HRTIM_CHPR_CARDTY_1)                                             /*!< Duty cycle of the carrier signal is 25 % */
#define LL_HRTIM_CHP_DUTYCYCLE_375  (HRTIM_CHPR_CARDTY_1 | HRTIM_CHPR_CARDTY_0)                       /*!< Duty cycle of the carrier signal is 37.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_500  (HRTIM_CHPR_CARDTY_2)                                             /*!< Duty cycle of the carrier signal is 50 % */
#define LL_HRTIM_CHP_DUTYCYCLE_625  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_0)                       /*!< Duty cycle of the carrier signal is 62.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_750  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_1)                       /*!< Duty cycle of the carrier signal is 75 % */
#define LL_HRTIM_CHP_DUTYCYCLE_875  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_1 | HRTIM_CHPR_CARDTY_0) /*!< Duty cycle of the carrier signal is 87.5 % */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CHP_PULSEWIDTH CHOPPER MODE PULSE WIDTH
  * @{
  * @brief Constants defining the pulse width of the first pulse of the generated high frequency carrier.
  */
#define LL_HRTIM_CHP_PULSEWIDTH_16   0x00000000U                                                                 /*!< tSTPW = tHRTIM x 16  */
#define LL_HRTIM_CHP_PULSEWIDTH_32   (HRTIM_CHPR_STRPW_0)                                                                 /*!< tSTPW = tHRTIM x 32  */
#define LL_HRTIM_CHP_PULSEWIDTH_48   (HRTIM_CHPR_STRPW_1)                                                                 /*!< tSTPW = tHRTIM x 48  */
#define LL_HRTIM_CHP_PULSEWIDTH_64   (HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 64  */
#define LL_HRTIM_CHP_PULSEWIDTH_80   (HRTIM_CHPR_STRPW_2)                                                                 /*!< tSTPW = tHRTIM x 80  */
#define LL_HRTIM_CHP_PULSEWIDTH_96   (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 96  */
#define LL_HRTIM_CHP_PULSEWIDTH_112  (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1)                                            /*!< tSTPW = tHRTIM x 112  */
#define LL_HRTIM_CHP_PULSEWIDTH_128  (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 128  */
#define LL_HRTIM_CHP_PULSEWIDTH_144  (HRTIM_CHPR_STRPW_3)                                                                 /*!< tSTPW = tHRTIM x 144  */
#define LL_HRTIM_CHP_PULSEWIDTH_160  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 160  */
#define LL_HRTIM_CHP_PULSEWIDTH_176  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_1)                                            /*!< tSTPW = tHRTIM x 176  */
#define LL_HRTIM_CHP_PULSEWIDTH_192  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 192  */
#define LL_HRTIM_CHP_PULSEWIDTH_208  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2)                                            /*!< tSTPW = tHRTIM x 208  */
#define LL_HRTIM_CHP_PULSEWIDTH_224  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 224  */
#define LL_HRTIM_CHP_PULSEWIDTH_240  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1)                       /*!< tSTPW = tHRTIM x 240  */
#define LL_HRTIM_CHP_PULSEWIDTH_256  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)  /*!< tSTPW = tHRTIM x 256  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CROSSBAR_INPUT CROSSBAR INPUT
  * @{
  * @brief Constants defining the events that can be selected to configure the set/reset crossbar of a timer output.
  */
#define LL_HRTIM_CROSSBAR_NONE       0x00000000U             /*!< Reset the output set crossbar */
#define LL_HRTIM_CROSSBAR_RESYNC     (HRTIM_SET1R_RESYNC)    /*!< Timer reset event coming solely from software or SYNC input forces an output level transision */
#define LL_HRTIM_CROSSBAR_TIMPER     (HRTIM_SET1R_PER)       /*!< Timer period event forces an output level transision */
#define LL_HRTIM_CROSSBAR_TIMCMP1    (HRTIM_SET1R_CMP1)      /*!< Timer compare 1 event forces an output level transision */
#define LL_HRTIM_CROSSBAR_TIMCMP2    (HRTIM_SET1R_CMP2)      /*!< Timer compare 2 event forces an output level transision */
#define LL_HRTIM_CROSSBAR_TIMCMP3    (HRTIM_SET1R_CMP3)      /*!< Timer compare 3 event forces an output level transision */
#define LL_HRTIM_CRO