

struct Drive_Engine_t
{
    int m_nSpeedRight;
    int m_nSpeedLeft;
    int m_nDirectionRight;
    int m_nDirectionLeft;
    int m_nStatus;
    int m_nLastState;

};

struct Drive_Engine_t init_engine(void)
{
    struct Drive_Engine_t engine;
    Port_DataDirBit(MOTOR_ENABLE,PORT_OUT);
    Port_WriteBit(MOTOR_ENABLE,0);
    Timer_T1PWMX(256,128,128,PS_8);
    Timer_T1PWA(128);
    Timer_T1PWB(128);

    engine.m_nSpeedRight = 0x0;
    engine.m_nSpeedLeft = 0x0;
    engine.m_nDirectionRight = ENGINE_FORWARD;
    engine.m_nDirectionLeft = ENGINE_FORWARD;
    engine.m_nStatus = ENGINE_OFF;
    engine.m_nLastState = ENGINE_OFF;
    return engine;
}

t_Result Update_engine(struct Drive_Engine_t engine)
{
    if (engine.m_nStatus != engine.m_nLastState)
    {
         if(engine.m_nStatus == ENGINE_OFF)
         {
            Port_WriteBit(MOTOR_ENABLE,0);
            engine.m_nLastState = engine.m_nStatus;
         }
         else if (engine.m_nStatus == ENGINE_ON)
         {
            Port_WriteBit(MOTOR_ENABLE,1);
            engine.m_nLastState = engine.m_nStatus;
         }
         else return ERR_STAT_UNSUPPORTED;
    }

    if(engine.m_nStatus == ENGINE_OFF) return SUCCESS;

    if(engine.m_nSpeedLeft <= 0 || engine.m_nSpeedLeft >= 100)
        return ERR_OUT_OF_RANGE;

    if(engine.m_nSpeedRight <= 0 || engine.m_nSpeedRight >= 100)
        return ERR_OUT_OF_RANGE;

    float sub_v_r;
    sub_v_r = engine.m_nSpeedRight * 1.28;
    float sub_v_l;
    sub_v_l = engine.m_nSpeedLeft *1.28;

    if(engine.m_nDirectionRight == ENGINE_FORWARD)
        sub_v_r = sub_v_r + 128;
    else if(engine.m_nDirectionRight == ENGINE_BACKWARD)
        sub_v_r = 128 - sub_v_r;
    else return ERR_DIR_UNSUPPORTED;

    if(engine.m_nDirectionLeft == ENGINE_FORWARD)
        sub_v_l = sub_v_l + 128;
    else if(engine.m_nDirectionLeft == ENGINE_BACKWARD)
        sub_v_l = 128 - sub_v_r;
    else return ERR_DIR_UNSUPPORTED;

    int v_r;
    v_r = sub_v_r;
    int v_l;
    v_l = sub_v_l;

    if(v_r > 255) v_r = 255;
    if(v_r < 0) v_r = 0;

    if(v_l > 255) v_l = 255;
    if(v_l < 0) v_l = 0;

    Timer_T1PWA(v_r);
    Timer_T1PWB(v_l);
    AbsDelay(250);

    return SUCCESS;
}