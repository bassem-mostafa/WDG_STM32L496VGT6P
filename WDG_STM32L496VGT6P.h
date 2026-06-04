// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

/**
 *  @file
 *
 *  @brief Platform WDG STM32L496VGT6P Driver
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_WDG_Driver
 *
 *  @{
 */

/**
 *  @defgroup Platform_WDG_STM32L496VGT6P STM32L496VGT6P
 *
 *  @{
 */

#ifndef WDG_STM32L496VGT6P_H_
    #define WDG_STM32L496VGT6P_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief WDG STM32L496VGT6P Operation Status
     *
     *  @enum WDG_STM32L496VGT6P_Status_t
     */
    typedef enum WDG_STM32L496VGT6P_Status
    {
        WDG_STM32L496VGT6P_Status_Success = 0,
        WDG_STM32L496VGT6P_Status_ArgumentInvalid,
        WDG_STM32L496VGT6P_Status_NotSupported,
        WDG_STM32L496VGT6P_Status_Error,
        WDG_STM32L496VGT6P_Status_Busy,
        WDG_STM32L496VGT6P_Status_Timeout,
    } WDG_STM32L496VGT6P_Status_t;

    /**
     *  @brief WDG STM32L496VGT6P
     *
     *  @enum WDG_STM32L496VGT6P_t
     */
    typedef enum WDG_STM32L496VGT6P
    {
        WDG_STM32L496VGT6P_1 = 0, ///< WDG 1 [IWDG] (Minimum)
        WDG_STM32L496VGT6P_2,     ///< WDG 2 [WWDG] (Maximum)
        WDG_STM32L496VGT6P_Count  ///< Count
    } WDG_STM32L496VGT6P_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    /**
     *  @brief Initializes specified WDG STM32L496VGT6P Instance
     *
     *  @param[in] WDGx Instance
     *
     *  @return WDG_STM32L496VGT6P_Status_t
     */
    WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Initialize( WDG_STM32L496VGT6P_t WDGx );

    /**
     *  @brief Cycles specified WDG STM32L496VGT6P Instance
     *
     *  @param[in] WDGx Instance
     *
     *  @return WDG_STM32L496VGT6P_Status_t
     */
    WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Cycle( WDG_STM32L496VGT6P_t WDGx );

    /**
     *  @brief De-initializes specified WDG STM32L496VGT6P Instance
     *
     *  @param[in] WDGx Instance
     *
     *  @return WDG_STM32L496VGT6P_Status_t
     */
    WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_DeInitialize( WDG_STM32L496VGT6P_t WDGx );

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char WDG_STM32L496VGT6P_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* WDG_STM32L496VGT6P_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
