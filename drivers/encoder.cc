

t_Result init_encoder(void)
{
    SPI_Disable();
    Port_DataDirBit(8,1);
    Port_WriteBit(8,1);

    Irq_SetVect(INT_6,_exec_enc_kernel_right);
    Irq_SetVect(INT_7,_exec_enc_kernel_left);

    Ext_IntEnable(6,1);
    Ext_IntEnable(7,1);

    return SUCCESS;
}

int encoder_get_difference(void)
{
    return _encoder_kernel(0b00001000);
}

word encoder_get_right(void)
{
    return _encoder_kernel(0b00010000);
}

word encoder_get_left(void)
{
    return _encoder_kernel(0b00100000);
}

void _exec_enc_kernel_right(void)
{
    int cnt;
    _encoder_kernel(0b00000010);
    cnt = Irq_GetCount(INT_6);
    return;
}

void _exec_enc_kernel_left(void)
{
    int  cnt;
    _encoder_kernel(0b00000100);
    cnt = Irq_GetCount(INT_7);
    return;
}

int _encoder_kernel(byte bitfield)
{
    static word incr_right;
    static word incr_left;

    if(bitfield & 0b00000001)
    {
        incr_right = 0;
        incr_left = 0;
        return 0;
    }

    if(bitfield & 0b00000010)
    {
        incr_right++;
        return 0;
    }

    if(bitfield & 0b00000100)
    {
        incr_left++;
        return 0;
    }

    if(bitfield & 0b00001000)
    {
        return incr_right - incr_left;
    }

    if(bitfield & 0b00010000)
    {
        return incr_right;
    }

    if(bitfield & 0b00100000)
    {
        return incr_left;
    }

    return 0;
}
