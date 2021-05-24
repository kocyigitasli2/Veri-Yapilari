#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct dugum {
	int deger;
	struct dugum *sol;
	struct dugum *sag;
}BTREE;
	
int adim=0;
int toplam=0;
int yaprakSayisi=0;

BTREE *dugumOlustur(int deger) {
	BTREE *yeniDugum = (BTREE*) malloc(sizeof(BTREE));
	yeniDugum -> deger = deger;
	yeniDugum -> sol = NULL;
	yeniDugum -> sag = NULL;
	return yeniDugum;
	}
	
BTREE *elemanEkle(BTREE *kok, int deger) {
	if(kok != NULL) {
		if(deger < kok -> deger)
			kok -> sol = elemanEkle(kok -> sol, deger);
		else
			kok -> sag = elemanEkle(kok -> sag, deger);
	}else
		kok = dugumOlustur(deger);
	return kok;
}

int elemanAra(BTREE* kok, int deger) {
	if(kok != NULL)
		if(kok -> deger == deger){
			adim++;
			return adim;
		}
	else if(kok -> deger > deger){
		adim++;
		elemanAra(kok -> sol, deger);
	}
	else{
		adim++;
		elemanAra(kok -> sag, deger);
	}
	else
		return -1;
}
void seviyedekiElemanlar(struct dugum* kok, int seviye) {
    if (kok == NULL)
        return;
    if (seviye == 1)
        printf("%d ", kok->deger);
    else if (seviye > 1)
    {
        seviyedekiElemanlar(kok->sol, seviye-1);
        seviyedekiElemanlar(kok->sag, seviye-1);
    }
}


void yaprakToplam(BTREE *kok, int& toplam){ 
    if (!kok) 
        return; 

    if (!kok->sol && !kok->sag){
        toplam += kok->deger;
		yaprakSayisi++; 
    }

    yaprakToplam(kok->sol, toplam); 
    yaprakToplam(kok->sag, toplam); 
}

void buyukEleman(BTREE *kok,int sayi) {
	if(kok != NULL) {
		if(kok->deger>sayi)
			printf("%d ",kok->deger);
		buyukEleman(kok -> sol,sayi);
		buyukEleman(kok -> sag,sayi);
	}
}


int main() {
	setlocale(LC_ALL,"Turkish");
	BTREE *kok = NULL;
	int sayi,secim,adimSayisi;
	double ort=0;
	while(true){
		adim=0,toplam=0,yaprakSayisi=0;
		system("CLS");
	    printf("\n|------------MENU-------------|");
	    printf("\n| 1>AÐACA EKLE                |");
	    printf("\n| 2>SEVÝYEDEKÝ ELEMANLARI GÖR |");
	    printf("\n| 3>ELEMAN ARA                |");
	    printf("\n| 4>YAPRAKLARIN ORTALAMASI    |");
	    printf("\n| 5>BÜYÜK DEÐERLERÝ GÖR       |");
	    printf("\n|-----------------------------|");
	    printf("\nSECIMINIZ --> ");
	    scanf("%d", &secim);
		switch(secim)
	    {
	        case 1:
	            printf("\nAðaca eklemek istediginiz sayýyý giriniz : ");
	            scanf("%d", &sayi);
	            kok=elemanEkle(kok,sayi);
	            printf("%d aðaca eklendi.\n",sayi);
	            printf("\nDevam etmek için bir tuþa basýnýz.");
	            getch();
	            break;
	        case 2:
	            printf("\nElemanlarýný görmek istediðiniz seviyeyi yazýnýz : ");
	            scanf("%d",&sayi);
	            printf("\n%d. seviyedeki elemanlar : ",sayi);
	            seviyedekiElemanlar(kok,sayi+1);
	            printf("\n\nDevam etmek için bir tuþa basýnýz.");
	            getch();
	            break;
	        case 3:
	        	printf("\nAramak istediðiniz elemaný yazýnýz : ");
	        	scanf("%d",&sayi);
	        	adimSayisi=elemanAra(kok,sayi);
	        	if(adimSayisi==-1){
	        		printf("\n%d elemaný bulunamadý!",sayi);
	        	}else{
	        		printf("\n%d elemaný %d adýmda bulundu.",sayi,adimSayisi);
				}
				printf("\n\nDevam etmek için bir tuþa basýnýz.");
	        	getch();
	        	break;
	        case 4:
	        	printf("\nYaprak düðümlerin ortalamasý : ");
	        	yaprakToplam(kok,toplam);
	        	ort = ((double)toplam / (double)yaprakSayisi);
	        	printf("%.2f",ort);
	        	printf("\n\nDevam etmek için bir tuþa basýnýz.");
	        	getch();
	        	break;
	        case 5:
	        	printf("\nLütfen bir deðer giriniz : ");
	        	scanf("%d",&sayi);
	        	printf("\n%d deðerinden büyük elemanlar : ",sayi);
	        	buyukEleman(kok,sayi);
	        	printf("\n\nDevam etmek için bir tuþa basýnýz.");
	        	getch();
	        	break;
	        default:
	        	printf("YANLIS GIRIS YAPILDI. LUTFEN 1 - 5 ARASI SECIM YAPINIZ!!!\n\n");
	        	printf("\nDevam etmek için bir tuþa basýnýz.");
	        	getch();
	    }
	}

	getch();
	return 0;
}
