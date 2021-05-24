#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


int kapasite; 

typedef struct {
    int musteri_no;
    char ad[20], soyad[20];
} Musteri;
 
Musteri veri_liste[10];
int hash_tablo[10][2];
Musteri yeni;


void hashInit(){               			//Baþlarken hash tablosunu -1 ile dolduruyoruz.
	for(int i=0;i<10;i++){
		hash_tablo[i][0]=-1;
		hash_tablo[i][1]=-1; 
	}
}

int bosYer(int deger, Musteri yeni){  		//Çakýþma olduðunda tabloya yerleþilecek yeri buluyoruz.
	int next;
   	if(hash_tablo[deger][1]==-1){
		for(int i=0;i<10;i++){
			if(hash_tablo[i][0]==-1){
				next=i;
				hash_tablo[i][0]=yeni.musteri_no;
				veri_liste[i]=yeni;
				hash_tablo[deger][1]=next;
				break;
			}
		}
	}
	else{
		deger=hash_tablo[deger][1];
		return bosYer(deger,yeni);
	}
}

int ekle(Musteri yeni){ 						//Ekleme fonksiyonu
	kapasite++;	
	int index;
	int next;
	int deger;
	index=yeni.musteri_no%10;
    
	if(hash_tablo[index][0]==-1){ 				//Tabloda index satýrýnda -1 yazýyor ise boþtur. Buraya ekleme yapýyoruz.
    	hash_tablo[index][0]=yeni.musteri_no;
    	veri_liste[index] = yeni;
    }
	else{										//Ýndex satýrý boþ deðilse bir yukarýdan ilk boþ yere yazýyoruz. Tablonun next kýsmýna da yerleþilen satýrýn indexini yazýyoruz.
		if(hash_tablo[index][1]==-1){
			for(int i=0; ; i++){
				if(hash_tablo[i][0]==-1){
					next=i;
					hash_tablo[i][0]=yeni.musteri_no;
					hash_tablo[index][1]=next;
					veri_liste[i]=yeni;
					break;
				}
			}
		}
		else{ 									//Eðer ikinci gidilen index yine dolu ise boþ yer aramaya devam ediyoruz.
			deger=hash_tablo[index][1];
			bosYer(deger,yeni);
			}
	}
}

void klavyedenEkleme(){
	if(kapasite!=10){
		Musteri yeni;
		printf("\nEklemek istediðiniz adýný giriniz: ");
		scanf("%s",&yeni.ad);
		printf("\nEklemek istediðiniz kiþinin soyadýný giriniz: ");
		scanf("%s",&yeni.soyad);
		printf("\nEklemek istediðiniz kiþinin numarasýný giriniz:");
		scanf("%d",&yeni.musteri_no);	
		ekle(yeni);
	}
	else{
		printf("\nBELLEK DOLU!!!\n");
	}
}

int varMi(int aranan){					//Ýstenilen numarayý hash tablosunda arýyoruz. Var ise 1 döndürüyor.
	for(int i=0;i<10;){
   	    if(aranan==hash_tablo[i][0]){
   	    	return 1;
		}  
	}   
}
  
int nextArama(int deger,int mod,int aranan,int sayac){	//Ýstenilen numaraya olmasý gereken yerde deðil ise kaç adýmda ulaþýldýðý bulunuyor
  	if(hash_tablo[deger][0]==aranan){
  		sayac++;
  		return sayac;
	}
	else{
		sayac++;
		deger=hash_tablo[deger][1];
		return nextArama(deger,mod,aranan,sayac);
	}
}
  
int arananAdimSayisi(int aranan){
  	int sayac=0;
   	int ara,sonuc,deger,mod;
  	mod=aranan%10;
  	if(varMi(aranan)==1){												//varMi=1 ise aranan eleman tabloda mevcuttur.
  		if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]==-1){		// Gidilen index'in gösterdiði baþka bir index yok ise aranan bulunmuþtur.
	    	sayac++;
	    	sonuc=sayac;
	    	printf("\nAranan deðer %d adýmda bulundu.\n",sonuc);
	    	return sonuc;
	  	}
		else if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]!=-1 && hash_tablo[mod][0]==aranan){	//Gidilen index baþka bir index gösteriyor ise indexler incelenip
	  	sayac++;																						//aranana eþit olan seçilmelidir.
	  	sonuc=sayac;
	  	printf("\nAranan deðer %d adýmda bulundu.\n",sonuc);
	  	return sonuc;
	  	}
    	else if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]!=-1){									//Gidilen index yine baþka bir index gösteriyor ise nextArama fonksiyonundan
    		sayac++;																					//arama yapýlýp adým sayýsý döndürülüyor.
    		deger=hash_tablo[mod][1];
    		sonuc=nextArama(deger,mod,aranan,sayac);
    		printf("\nAranan deðer %d adýmda bulundu.\n",sonuc);
    		return sonuc;
		}
		else{
			sayac++;
	  		sonuc=sayac;
	  		printf("\nAranan deðer %d adýmda bulundu.\n",sonuc);
	  		return sonuc;
		}	  
	}
	else{
	  	printf("\nAranan deðer bulunamadý. Lütfen farklý bir deðer ile deneyiniz.\n");
	}
}

void veriListeYazdir(){
	for(int i=0;i<10;i++){ 
		printf("%d %s %s\n",veri_liste[i].musteri_no,veri_liste[i].ad,veri_liste[i].soyad);
	}
}

 void hashTabloYazdir(){
	printf("\n|---HASH TABLOSU---|\n");
	for(int i=0;i<10;i++){ 
		printf("   %d --> %d\n",hash_tablo[i][0],hash_tablo[i][1]);
	}
}

void veriSilme(){
  	int silinecek;
  	printf("\nSilmek istediðiniz kiþinin numarasýný giriniz: ");
  	scanf("%d",&silinecek);
  	for(int i=0;i<10;i++){	
  		if(silinecek==hash_tablo[i][0]){
  			hash_tablo[i][0]=-1;
		}  
	}
}




int main(){
	setlocale(LC_ALL,"Turkish");
	int secim,sayi;
	hashInit();
	FILE* dosya;
	dosya = fopen("veri.txt","r");
	while(!feof(dosya)){
		Musteri yeni; 
	  	fscanf(dosya,"%d",&yeni.musteri_no);
	  	fscanf(dosya,"%s %s",yeni.ad,yeni.soyad);
	    ekle(yeni);  
	}
	while(1){
		printf("\n|  ÝÞLEM MENÜSÜ  |\n");
		printf("------------------\n");
		printf("| 1)Müþteri Ekle |\n");
		printf("| 2)Müþteri Ara  |\n");
		printf("| 3)Müþteri Sil  |\n");
		printf("| 4)Hash Tablosu |\n");
		printf("| 5)Veri Listesi |\n");
		printf("------------------\n");
		printf("\nSeçiminiz: ");
		scanf("%d",&secim);

		switch(secim){	
			case 1:
				system("CLS");
				 klavyedenEkleme();
				 break;		 
			case 2:
				system("CLS");
				printf("\nArayacaðýnýz müþterinin numarasýný giriniz: ");
				scanf("%d",&sayi);
				arananAdimSayisi(sayi);
				break;		
			case 3:
				system("CLS");
				veriSilme();
				hashTabloYazdir();
				break;	
			case 4:
				system("CLS");
			    hashTabloYazdir();
				break;	
			case 5:
				system("CLS");
			    veriListeYazdir();
			    break;	
		}
	}         
	getch();
	return 0;       
}

