#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <stdlib.h>

asmlinkage long sys_hashtag_partiu_ordenar(int *a, int l, int r);

int partition(int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while(1){
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;

   return j;
}

void quickSort(int a[], int l, int r){

	int j;
	
	if(l<r){
 	  // DIIVIDIR E CONQUISTAR
	  j = partition(a, l, r);
	  quickSort(a, l, j-1);
	  quickSort(a, j+1, r);
	}
}

asmlinkage long sys_hashtag_partiu_ordenar(int *a, int l, int r) {
	int i;

	printk("Lista recebida: ");
	for(i=0; i<r; i++)
		printk("%d ", a[i]);
	printk("\n");

	quickSort(a, 0, (r-1));

	printk("Lista ordenada: ");
	for(i=0; i<r; ++i)
		printk("%d ", a[i]);
	printk("\n");

	return 0;
}
