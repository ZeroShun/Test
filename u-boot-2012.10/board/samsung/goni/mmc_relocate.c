typedef unsigned int (*copy_sd_mmc_to_mem) (unsigned int  channel, unsigned int  start_block, unsigned char block_size, unsigned int  *trg, unsigned int  init);


void copy_code_to_dram(void)
{
	unsigned long ch;
	unsigned long dest = 0x34800000;  //���ص�Ŀ���ַ
	unsigned int sec_no = 49;  //������ʼ��ַ

	ch = *(volatile unsigned int *)(0xD0037488);

	// ����ָ��
	copy_sd_mmc_to_mem copy_bl2 = (copy_sd_mmc_to_mem) (*(unsigned int *) (0xD0037F98));

	unsigned int ret;
	
	// ͨ��0
	if (ch == 0xEB000000)
	{
		// 0:channel 0
		// 49:Դ����λ������49,1 sector = 512 bytes
		// 32:���ȣ�����32 sector����16K
		// 0x23E00000:Ŀ��,���ӵ�ַ0x23E00000
		ret = copy_bl2(0, sec_no,       128, (unsigned int *)dest, 0);  //64k
		ret = copy_bl2(0, sec_no + 128, 128, (unsigned int *)(dest+ 0x10000), 0);  //64k
		ret = copy_bl2(0, sec_no + 256, 128, (unsigned int *)(dest + 0x20000), 0);    //64k
	}
}