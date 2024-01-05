#define NO_OFFSET 0xfffffffffffff000
#define NO_NX_FLAG 0xffffffffffffefff
#define PAGE_OFFSET 0xffff880000000000

void get_PT_address() {
	unsigned long int *pud_phys, *pmd_phys, *pte_phys, *NPF, *pmd, *pte, *pud,
		*NPV;

	unsigned long int word_addr;

	int word;
	printk("INIZIO PAGE WALK");

	// accedo pud

	pud_phys = (unsigned long int *)pgd[ind.pgd_indice];

	pud_phys = (unsigned long int)pud_phys & NO_OFFSET;

	pud = pud_phys + PAGE_OFFSET / 8;

	printk("indirizzo di PUD = 0x%16.16lx\n", pud);

	// accedo pmd

	pmd_phys = (unsigned long int *)pud[ind.pud_indice];

	pmd_phys = (unsigned long int)pmd_phys & NO_OFFSET;

	pmd = pmd_phys + PAGE_OFFSET / 8;

	printk("indirizzo di PMD = 0x%16.16lx\n", pmd);

	// accedo pt

	pte_phys = (unsigned long int *)pmd[ind.pmd_indice];

	pte_phys = (unsigned long int)pte_phys & NO_OFFSET;

	pte = pte_phys + PAGE_OFFSET / 8;

	printk("indirizzo di  PT = 0x%16.16lx\n", pte);

	// accedo NPF

	NPF = (unsigned long int *)pte[ind.pt_indice];

	NPF = (unsigned long int)NPF & NO_OFFSET;
	printk("NPF (con NX flag non azzerato) = 0x%16.16lx\n",
		   (long unsigned int)NPF);

	NPF = (unsigned long int)NPF & NO_NX_FLAG;

	printk("NPF (con NX flag azzerato) = 0x%16.16lx\n", (long unsigned int)NPF);

	// determina l’indirizzo completo della parola
	NPV = NPF + PAGE_OFFSET / 8;

	printk("NPV = 0x%16.16lx\n", (long unsigned int)NPV);

	word_addr = (unsigned long int)NPV + ind.offset;

	printk("Indirizzo virtuale completo = 0x%16.16lx\n", word_addr);

	word = *((int *)word_addr);

	printk("Parola letta all'indirizzo virtuale derivato da fisico = %d\n",
		   word);
}
