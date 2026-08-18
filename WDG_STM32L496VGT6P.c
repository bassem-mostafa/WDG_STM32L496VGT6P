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

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef STM32L496xx

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../WDG_Internal.h"
    #include "WDG_STM32L496VGT6P.h"

    #include "stm32l4xx.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

/**
 * @brief WDG STM32L496VGT6P Operation
 *
 * @enum WDG_STM32L496VGT6P_OperationType_t
 */
typedef enum WDG_STM32L496VGT6P_OperationType
{
    WDG_STM32L496VGT6P_OperationType_None = 0, ///< None
    WDG_STM32L496VGT6P_OperationType_Pending,  ///< Pending
    WDG_STM32L496VGT6P_OperationType_Commit,   ///< Commit
} WDG_STM32L496VGT6P_OperationType_t;

/**
 * @brief WDG STM32L496VGT6P Operation Handler
 */
typedef WDG_STM32L496VGT6P_Status_t ( *WDG_STM32L496VGT6P_OperationHandler_t )( WDG_STM32L496VGT6P_t WDGx );

/**
 * @brief WDG STM32L496VGT6P Operation Context
 *
 * @struct WDG_STM32L496VGT6P_OperationContext_t
 */
typedef struct WDG_STM32L496VGT6P_OperationContext
{
} WDG_STM32L496VGT6P_OperationContext_t;

/**
 * @brief WDG STM32L496VGT6P Operation
 *
 * @struct WDG_STM32L496VGT6P_Operation_t
 */
typedef struct WDG_STM32L496VGT6P_Operation
{
    WDG_STM32L496VGT6P_OperationType_t Type;       ///< Type
    WDG_STM32L496VGT6P_OperationHandler_t Handler; ///< Handler
    WDG_STM32L496VGT6P_Status_t Status;            ///< Status
    TIM_Timestamp_t Timeout;                       ///< Timeout
    WDG_STM32L496VGT6P_OperationContext_t Context; ///< Context
} WDG_STM32L496VGT6P_Operation_t;

/**
 * @brief WDG STM32L496VGT6P Process Type
 *
 * @enum WDG_STM32L496VGT6P_ProcessType_t
 */
typedef enum WDG_STM32L496VGT6P_ProcessType
{
    WDG_STM32L496VGT6P_ProcessType_None = 0,   ///< None
    WDG_STM32L496VGT6P_ProcessType_Initialize, ///< Initialize
} WDG_STM32L496VGT6P_ProcessType_t;

/**
 * @brief WDG STM32L496VGT6P Process Handler
 */
typedef WDG_STM32L496VGT6P_Status_t ( *WDG_STM32L496VGT6P_ProcessHandler_t )( WDG_STM32L496VGT6P_t WDGx );

/**
 * @brief WDG STM32L496VGT6P Process Context
 *
 * @struct WDG_STM32L496VGT6P_ProcessContext_t
 */
typedef struct WDG_STM32L496VGT6P_ProcessContext
{
    WDG_STM32L496VGT6P_Operation_t Operation; ///< Operation
} WDG_STM32L496VGT6P_ProcessContext_t;

/**
 * @brief WDG STM32L496VGT6P Process
 *
 * @struct WDG_STM32L496VGT6P_Process_t
 */
typedef struct WDG_STM32L496VGT6P_Process
{
    WDG_STM32L496VGT6P_ProcessType_t Type;       ///< Type
    WDG_STM32L496VGT6P_ProcessHandler_t Handler; ///< Handler
    WDG_STM32L496VGT6P_ProcessContext_t Context; ///< Context
} WDG_STM32L496VGT6P_Process_t;

typedef enum WDG_STM32L496VGT6P_Event
{
    WDG_STM32L496VGT6P_Event_None = 0,
    WDG_STM32L496VGT6P_Event_Interrupt = UTIL_BIT( 0 ),
} WDG_STM32L496VGT6P_Event_t;

typedef struct WDG_STM32L496VGT6P_Instance
{
    IWDG_HandleTypeDef IWDGx;
    WWDG_HandleTypeDef WWDGx;

    WDG_STM32L496VGT6P_Event_t Event;

    WDG_STM32L496VGT6P_Process_t Process;
} WDG_STM32L496VGT6P_Instance_t;

typedef struct WDG_STM32L496VGT6P_Context
{
    TIM_Timestamp_t Timestamp;
    WDG_STM32L496VGT6P_Instance_t Instance[ WDG_STM32L496VGT6P_Count ];
} WDG_STM32L496VGT6P_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_Initialize( void );
static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_Cycle( void );
static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_DeInitialize( void );

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_Initialize( WDG_STM32L496VGT6P_t WDGx );
static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_Cycle( WDG_STM32L496VGT6P_t WDGx );
static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_DeInitialize( WDG_STM32L496VGT6P_t WDGx );

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_SetProcess( WDG_STM32L496VGT6P_t WDGx, WDG_STM32L496VGT6P_ProcessType_t ProcessType );

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_ProcessInitialize( WDG_STM32L496VGT6P_t WDGx );

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_OperationCommitExecute( WDG_STM32L496VGT6P_t WDGx );
static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_OperationCommitResolve( WDG_STM32L496VGT6P_t WDGx );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static WDG_STM32L496VGT6P_Context_t WDG_STM32L496VGT6P_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

void WWDG_IRQHandler( void )
{
    WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDG_STM32L496VGT6P_2 ];

    Instance->Event |= WDG_STM32L496VGT6P_Event_Interrupt;

    HAL_WWDG_IRQHandler( &Instance->WWDGx );
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_Initialize( void )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( void )", __FUNCTION__ );

        // FIXME Remove the usage of `MX_IWDG_Init()`
    #if 1
        extern IWDG_HandleTypeDef hiwdg;
        extern void MX_IWDG_Init( void );
        MX_IWDG_Init( );
        {
            WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDG_STM32L496VGT6P_1 ];
            Instance->IWDGx = hiwdg;
        }
    #endif

        // FIXME Remove the usage of `MX_WWDG_Init()`
    #if 0
        extern WWDG_HandleTypeDef hwwdg;
        extern void MX_WWDG_Init( void );
        MX_WWDG_Init( );
        {
            WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDG_STM32L496VGT6P_2 ];
            Instance->WWDGx = hwwdg;
        }
    #endif
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_Cycle( void )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( WDG_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Context_DeInitialize( void )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( WDG_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_Initialize( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];

        switch ( WDGx )
        {
            case WDG_STM32L496VGT6P_1:
                break;

            case WDG_STM32L496VGT6P_2:
                break;

            default:
                Status = WDG_STM32L496VGT6P_Status_NotSupported;
                break;
        }
        if ( Status != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Instance->Event = WDG_STM32L496VGT6P_Event_None;

        Status = WDG_STM32L496VGT6P_SetProcess( WDGx, WDG_STM32L496VGT6P_ProcessType_Initialize );
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_Cycle( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;
    WDG_STM32L496VGT6P_Status_t STM32L496VGT6P_Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];

        WDG_STM32L496VGT6P_Process_t * Process = &Instance->Process;
        WDG_STM32L496VGT6P_Operation_t * Operation = &Process->Context.Operation;
        WDG_STM32L496VGT6P_Event_t Event = Instance->Event; // CAUTION: Has to copy events occurred at the early start of the cycle, so as to be cleared at the end of the cycle,
                                                            //          which let events occurs after that for the next cycle call
        Instance->Event &= ~Event;                          //          Clear captured events

        if ( Operation->Handler != NULL )
        {
            if ( ( STM32L496VGT6P_Status = Operation->Handler( WDGx ) ) != WDG_STM32L496VGT6P_Status_Success )
            {
                Status = STM32L496VGT6P_Status;
                // FIXME Operation reported non success status, is there any action?
            }
        }

        if ( Process->Handler != NULL )
        {
            if ( ( STM32L496VGT6P_Status = Process->Handler( WDGx ) ) != WDG_STM32L496VGT6P_Status_Success )
            {
                Status = STM32L496VGT6P_Status;
                // FIXME Process reported non success status, is there any action?
            }
        }

        if ( ( Event & WDG_STM32L496VGT6P_Event_Interrupt ) == WDG_STM32L496VGT6P_Event_Interrupt )
        {
            Event &= ~WDG_STM32L496VGT6P_Event_Interrupt;
            WDG_Trace( "Interrupt: WDGx=%d", WDGx );
            // TODO Invoke Callback
        }

        if ( Event )
        {
            WDG_Warning( "Not handled events %X: WDGx=%d", Event, WDGx );
        }

        switch ( WDGx )
        {
            case WDG_STM32L496VGT6P_1:
                HAL_IWDG_Refresh( &Instance->IWDGx );
                break;

            case WDG_STM32L496VGT6P_2:
                //                HAL_WWDG_Refresh( &Instance->WWDGx );
                break;

            default:
                break;
        }
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Instance_DeInitialize( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;
    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];

        UTIL_UNUSED( Instance );

        // FIXME
        Status = WDG_STM32L496VGT6P_Status_NotSupported;
    }
    while ( 0 );
    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_SetProcess( WDG_STM32L496VGT6P_t WDGx, WDG_STM32L496VGT6P_ProcessType_t ProcessType )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d, ProcessType=%d )", __FUNCTION__, WDGx, ProcessType );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];
        WDG_STM32L496VGT6P_Process_t * Process = &Instance->Process;
        WDG_STM32L496VGT6P_Operation_t * Operation = &Process->Context.Operation;

        switch ( ProcessType )
        {
            case WDG_STM32L496VGT6P_ProcessType_None:
                Process->Handler = NULL;
                break;

            case WDG_STM32L496VGT6P_ProcessType_Initialize:
                Process->Handler = WDG_STM32L496VGT6P_ProcessInitialize;
                break;

            default:
                WDG_Warning( "%s Not Handled Type %d", __FUNCTION__, ProcessType );
                Status = WDG_STM32L496VGT6P_Status_NotSupported;
                break;
        }
        if ( Status != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Process->Type = ProcessType;

        Operation->Handler = NULL;
        Operation->Status = WDG_STM32L496VGT6P_Status_Success;
        Operation->Timeout = WDG_STM32L496VGT6P_Context.Timestamp;

        switch ( ProcessType )
        {
            case WDG_STM32L496VGT6P_ProcessType_None:
                Operation->Type = WDG_STM32L496VGT6P_OperationType_None;
                break;

            default:
                Operation->Type = WDG_STM32L496VGT6P_OperationType_Pending;
                break;
        }
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_ProcessInitialize( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];
        WDG_STM32L496VGT6P_Process_t * Process = &Instance->Process;
        WDG_STM32L496VGT6P_Operation_t * Operation = &Process->Context.Operation;

        if ( Process->Type != WDG_STM32L496VGT6P_ProcessType_Initialize )
        {
            WDG_Error( "%s Got %d Expected %d", __FUNCTION__, Process->Type, WDG_STM32L496VGT6P_ProcessType_Initialize );
            Status = WDG_STM32L496VGT6P_Status_Error;
            break;
        }

        if ( Operation->Handler != NULL )
        {
            // Operation In-progress
            break;
        }

        if ( Operation->Status != WDG_STM32L496VGT6P_Status_Success )
        {
            Operation->Type = WDG_STM32L496VGT6P_OperationType_None;
        }

        switch ( Operation->Type )
        {
            case WDG_STM32L496VGT6P_OperationType_Pending:
                Operation->Status = WDG_STM32L496VGT6P_OperationCommitExecute( WDGx );
                break;

            case WDG_STM32L496VGT6P_OperationType_Commit:
            default:
                // TODO Invoke Callback
                // if ( Instance->OnComplete != NULL)
                //{
                //     Instance->OnComplete( WDGx, Operation->Status );
                //}
                Status = WDG_STM32L496VGT6P_SetProcess( WDGx, WDG_STM32L496VGT6P_ProcessType_None );
                break;
        }
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_OperationCommitExecute( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];
        WDG_STM32L496VGT6P_Process_t * Process = &Instance->Process;
        WDG_STM32L496VGT6P_Operation_t * Operation = &Process->Context.Operation;

    // FIXME Keep CubeMX generated configurations as is for now
    #if 0
      HAL_StatusTypeDef HAL_Status = HAL_ERROR;
      if ( ( HAL_Status = HAL_IWDG_Init( &Instance->Context->WDGx ) ) != HAL_OK )
      {
        Status = WDG_STM32L496VGT6P_Status_Error;
        break;
}
      if ( ( HAL_Status = HAL_WWDG_Init( &Instance->Context->WDGx ) ) != HAL_OK )
      {
        Status = WDG_STM32L496VGT6P_Status_Error;
        break;
}
    #endif

        __HAL_DBGMCU_FREEZE_IWDG( );

        Operation->Type = WDG_STM32L496VGT6P_OperationType_Commit;
        Operation->Handler = WDG_STM32L496VGT6P_OperationCommitResolve;
        Operation->Status = WDG_STM32L496VGT6P_Status_Success;
        Operation->Timeout = WDG_STM32L496VGT6P_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 0 ) ) != TIM_Status_Success )
        {
            Status = WDG_STM32L496VGT6P_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_OperationCommitResolve( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        WDG_STM32L496VGT6P_Instance_t * Instance = &WDG_STM32L496VGT6P_Context.Instance[ WDGx ];
        WDG_STM32L496VGT6P_Process_t * Process = &Instance->Process;
        WDG_STM32L496VGT6P_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != WDG_STM32L496VGT6P_OperationType_Commit )
        {
            WDG_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, WDG_STM32L496VGT6P_OperationType_Commit );
            Status = WDG_STM32L496VGT6P_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( WDG_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = WDG_STM32L496VGT6P_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Initialize( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        if ( ( Status = WDG_STM32L496VGT6P_Context_Initialize( ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = WDG_STM32L496VGT6P_Instance_Initialize( WDGx ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_Cycle( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        if ( ( Status = WDG_STM32L496VGT6P_Context_Cycle( ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = WDG_STM32L496VGT6P_Instance_Cycle( WDGx ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

WDG_STM32L496VGT6P_Status_t WDG_STM32L496VGT6P_DeInitialize( WDG_STM32L496VGT6P_t WDGx )
{
    WDG_STM32L496VGT6P_Status_t Status = WDG_STM32L496VGT6P_Status_Success;

    do
    {
        WDG_Trace( "%s( WDGx=%d )", __FUNCTION__, WDGx );

        if ( ( Status = WDG_STM32L496VGT6P_Instance_DeInitialize( WDGx ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = WDG_STM32L496VGT6P_Context_DeInitialize( ) ) != WDG_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char WDG_STM32L496VGT6P_VERSION[] = "0.0.0.v20260818-0345";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* STM32L496xx */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
