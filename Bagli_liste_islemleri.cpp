#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int sayac[10]={0};
int elemanSayisi=0;
typedef struct bagliListe{
	char isim[50];
	char soyisim[50];
	int numara;
	struct bagliListe *sonraki;
	//sayac[gecici->numara%10]
};
bagliListe *ilk=NULL,*son=NULL,*gecici;

void yerDegistir(bagliListe *gelen1, bagliListe *gelen2) //Düðümlerin yer deðiþtirmesi için gerekli fonksiyon 
{
	bagliListe *gecici;
    gecici = gelen1;
    gelen1= gelen2;
    gelen2 = gecici;
}

void tekrarSirala(bagliListe *ilk) { // Listedeki düðümleri istenilen þekilde sýralamak için gerekli fonksiyon
    int sayac2[10] = { 0 };
    bagliListe *gecici = ilk;
    while (gecici != NULL) {
        sayac2[gecici->numara%10]++;
        gecici = gecici->sonraki;
    }
    bool yerDegisti = 1;
    bagliListe *gecici2;
    bagliListe *gecici3 = NULL;
    do {
        yerDegisti = 0;
        gecici2 = ilk;
    	while (gecici2->sonraki != gecici3) {
        	if (sayac2[(gecici2)->numara%10] < sayac2[(gecici2->sonraki)->numara%10]) {
            	yerDegistir(gecici2, gecici2->sonraki);
            	yerDegisti = 1;
        	}
            gecici2 = gecici2->sonraki;
    	}
        gecici3 = gecici2;
        printf("Calisti");
    }while (yerDegisti);
}

void ekle(bagliListe *eklenecek){
    gecici=ilk;
    if (ilk==NULL) {
        ilk = eklenecek;
        son = eklenecek;
    }else if(sayac[eklenecek->numara%10]>sayac[gecici->numara%10]){  //yeni eklenen daha çok tekrarlanýyor ise
        ilk=eklenecek;
        ilk->sonraki=gecici;
	}else if(sayac[eklenecek->numara%10]<sayac[gecici->numara%10]){ //yeni eklenen daha az tekrarlanýyor ise
		while(sayac[eklenecek->numara%10]<sayac[gecici->numara%10] && gecici->sonraki!=NULL){
			gecici=gecici->sonraki;
			}
		eklenecek->sonraki=gecici->sonraki;
		gecici->sonraki=eklenecek;
	}else if(sayac[eklenecek->numara%10]==sayac[gecici->numara%10]){  //yeni eklenen ile tekrar sayýsý ayný ise
		if(eklenecek->numara%10>gecici->numara%10){  //eklenen ilkten büyükse
			ilk=eklenecek;
			ilk->sonraki=gecici;
		}else if(eklenecek->numara%10<gecici->numara%10){ //eklenen ilkten küçükse
			while(eklenecek->numara%10<gecici->numara%10 && gecici->sonraki!=NULL)
				gecici=gecici->sonraki;
			eklenecek->sonraki=gecici->sonraki;
			gecici->sonraki=eklenecek;	
		}else if(eklenecek->numara%10==gecici->numara%10){ //ilke eþitse
			eklenecek->sonraki=gecici->sonraki;
			gecici->sonraki=eklenecek;		
		}
	}
}
void deneme(FILE *fp){
	int sayi=0;
	int deneme=0;
	while(!feof(fp)){
		fscanf(fp,"%d %s %s",&sayi);
		sayi=sayi%10;
		sayac[sayi]++;
		printf("-",sayac[sayi]);		
	}
}
void dosyadanOku(FILE *fp){
	printf("\n");
	while(!feof(fp)){

 		bagliListe *kayit=(bagliListe *)malloc(sizeof(bagliListe));
	 	fscanf(fp,"%d %s %s",&kayit->numara,&kayit->isim,&kayit->soyisim);
	 	kayit->sonraki=NULL;
		ekle(kayit);
	}
}
void ekranaYazdir(bagliListe *ilk){
	gecici=ilk;
	while(gecici!=NULL){
		printf("%d %s %s\n",gecici->numara,gecici->isim,gecici->soyisim);
		gecici=gecici->sonraki;
		}
}
void arama(bagliListe *ilk, int aranan){
	gecici=ilk;
	int adim=1;
	while(gecici->numara!=aranan){
		gecici=gecici->sonraki;
		adim++;
		if(gecici==NULL)
			printf("Aranan kayit bulunamamistir.\n");
	}
	printf("%d %s %s -- Kayit %d adimda bulunmustur.",gecici->numara,gecici->isim,gecici->soyisim,adim);
}
void elemanSil(bagliListe *ilk, int aranan){
	gecici=ilk;
	bagliListe *silinecek;
	
	if(ilk->numara==aranan){
		silinecek=ilk;
		ilk=ilk->sonraki;
		free(silinecek);
		tekrarSirala(ilk);
	}else{
		while(gecici->sonraki->numara!=aranan){
			gecici=gecici->sonraki;
			if(gecici==NULL)
				printf("Kayit bulunamamistir\n");
		}
		silinecek=gecici->sonraki;
		sayac[silinecek->numara%10]--;
		gecici->sonraki=gecici->sonraki->sonraki;
		free(silinecek);
		tekrarSirala(ilk);
	}
}
void dosyayaYazdir(bagliListe *ilk){
	FILE *dosyaYaz = fopen("liste_final.txt","w");
	gecici=ilk;
	while(gecici!=NULL){
		fprintf(dosyaYaz,"%d %s %s\n",gecici->numara,gecici->isim,gecici->soyisim);
		gecici=gecici->sonraki;
	}
}

 int main(){
 	int secenek,arananKayit,silinecekNumara;
 	FILE *dosya=fopen("text.txt","r");
 	deneme(dosya);
 	fclose(dosya);
 	FILE *dp=fopen("text.txt","r");
	dosyadanOku(dp);
	printf("\n");
	fflush(stdin);
aa:
	printf("1.Ekleme\n2.Listeleme\n3.Arama\n4.Silme\n5.Cikis\n\nYapmak istediginiz islemi seciniz : ");
	scanf("%d",&secenek);
	if(secenek>5 || secenek<1)
	{
		system("CLS");
		printf("\nHatali giris yaptiniz.\n");
		printf("\nMenu'ye donmek icin bir tusa basiniz.\n");
		getch();
		system("CLS");
		goto aa;
	}
	
	switch(secenek){
		case 1 :
		{
			system("CLS");
			bagliListe *yeniKayit=(bagliListe *)malloc(sizeof(bagliListe));
			fflush(stdin);
			printf("\nNumara bilgisi giriniz: ");
			scanf("%d",&yeniKayit->numara);
			fflush(stdin);
			printf("\nÝsim bilgisi giriniz: ");
			scanf("%s",&yeniKayit->isim);
			fflush(stdin);
			printf("\nSoyisim bilgisi giriniz: ");
			scanf("%s",&yeniKayit->soyisim);
			fflush(stdin);
	 		yeniKayit->sonraki=NULL;
			ekle(yeniKayit);
			printf("\nMenu'ye donmek icin bir tusa basiniz.\n");
			getch();
			system("CLS");
			goto aa;
		}
		case 2 :
		{	system("CLS");
			ekranaYazdir(ilk);
			printf("\nMenu'ye donmek icin bir tusa basiniz.\n");
			getch();
			system("CLS");
			goto aa;
		}
		
		case 3 :
		{	system("CLS");
			printf("\nAramak istediðiniz numarayi giriniz: ");
			scanf("%d",&arananKayit);
			arama(ilk,arananKayit);
			printf("\nMenu'ye donmek icin bir tusa basiniz.\n");
			getch();
			system("CLS");
			goto aa;
		}
		case 4 :
		{
			system("CLS");
			printf("\nSilmek istediðiniz numara: ");
			scanf("%d",&silinecekNumara);
			elemanSil(ilk,silinecekNumara);
			printf("\nMenu'ye donmek icin bir tusa basiniz.\n");
			getch();
			system("CLS");
			goto aa;
		}
		case 5 :
		{
			system("CLS");
			dosyayaYazdir(ilk);
			printf("\nÝslem tamamlandi. Cikmak icin bir tusa basiniz. \n");
			getch();
			return 0;
		}
	}

    		
 }
