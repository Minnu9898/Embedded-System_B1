
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_CLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_CLK_EN();
		}else if (pSPIx == SPI3)
		{
			SPI3_CLK_EN();
		}else if (pSPIx == SPI4)
		{
			SPI4_CLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_CLK_DI();
		}else if (pSPIx == SPI2)
		{
			SPI2_CLK_DI();
		}else if (pSPIx == SPI3)
		{
			SPI3_CLK_DI();
		}else if (pSPIx == SPI4)
		{
			SPI4_CLK_DI();
		}
	}
}
