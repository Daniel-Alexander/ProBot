

struct pid_controler_t
{
    byte k_p;
    byte k_d;
    byte k_i;
};

struct pid_controler_t init_pid_controler(void)
{
    struct pid_controler_t controler;
    controler.k_p = 1;
    controler.k_d = 0;
    controler.k_i = 0;
    return controler;
}

struct Drive_Engine_t pid_engine_control(struct Drive_Engine_t engine, struct pid_controler_t controler, int error)
{
    int set;
    set = (error * controler.k_p);

    if(set == 0) return engine;

    if(set > 0)
    {
        engine.m_nSpeedRight = engine.m_nSpeedRight + set;
        if(engine.m_nSpeedRight >= 70)
        {
            //engine.m_nSpeedRight = engine.m_nSpeedRight - set;
            //engine.m_nSpeedLeft = engine.m_nSpeedLeft - set;
        }
        return engine;
    }

    if(set < 0)
    {
        engine.m_nSpeedLeft = engine.m_nSpeedLeft - set;
        if(engine.m_nSpeedLeft >= 70)
        {
            //engine.m_nSpeedLeft = engine.m_nSpeedLeft + set;
            //engine.m_nSpeedRight = engine.m_nSpeedRight + set;
        }
        return engine;
    }

}
