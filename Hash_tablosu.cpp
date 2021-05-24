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


void hashInit(){               			//Ba�larken hash tablosunu -1 ile dolduruyoruz.
	for(int i=0;i<10;i++){
		hash_tablo[i][0]=-1;
		hash_tablo[i][1]=-1; 
	}
}

int bosYer(int deger, Musteri yeni){  		//�ak��ma oldu�unda tabloya yerle�ilecek yeri buluyoruz.
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
    
	if(hash_tablo[index][0]==-1){ 				//Tabloda index sat�r�nda -1 yaz�yor ise bo�tur. Buraya ekleme yap�yoruz.
    	hash_tablo[index][0]=yeni.musteri_no;
    	veri_liste[index] = yeni;
    }
	else{										//�ndex sat�r� bo� de�ilse bir yukar�dan ilk bo� yere yaz�yoruz. Tablonun next k�sm�na da yerle�ilen sat�r�n indexini yaz�yoruz.
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
		else{ 									//E�er ikinci gidilen index yine dolu ise bo� yer aramaya devam ediyoruz.
			deger=hash_tablo[index][1];
			bosYer(deger,yeni);
			}
	}
}

void klavyedenEkleme(){
	if(kapasite!=10){
		Musteri yeni;
		printf("\nEklemek istedi�iniz ad�n� giriniz: ");
		scanf("%s",&yeni.ad);
		printf("\nEklemek istedi�iniz ki�inin soyad�n� giriniz: ");
		scanf("%s",&yeni.soyad);
		printf("\nEklemek istedi�iniz ki�inin numaras�n� giriniz:");
		scanf("%d",&yeni.musteri_no);	
		ekle(yeni);
	}
	else{
		printf("\nBELLEK DOLU!!!\n");
	}
}

int varMi(int aranan){					//�stenilen numaray� hash tablosunda ar�yoruz. Var ise 1 d�nd�r�yor.
	for(int i=0;i<10;){
   	    if(aranan==hash_tablo[i][0]){
   	    	return 1;
		}  
	}   
}
  
int nextArama(int deger,int mod,int aranan,int sayac){	//�stenilen numaraya olmas� gereken yerde de�il ise ka� ad�mda ula��ld��� bulunuyor
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
  		if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]==-1){		// Gidilen index'in g�sterdi�i ba�ka bir index yok ise aranan bulunmu�tur.
	    	sayac++;
	    	sonuc=sayac;
	    	printf("\nAranan de�er %d ad�mda bulundu.\n",sonuc);
	    	return sonuc;
	  	}
		else if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]!=-1 && hash_tablo[mod][0]==aranan){	//Gidilen index ba�ka bir index g�steriyor ise indexler incelenip
	  	sayac++;																						//aranana e�it olan se�ilmelidir.
	  	sonuc=sayac;
	  	printf("\nAranan de�er %d ad�mda bulundu.\n",sonuc);
	  	return sonuc;
	  	}
    	else if(mod==hash_tablo[mod][0]%10 && hash_tablo[mod][1]!=-1){									//Gidilen index yine ba�ka bir index g�steriyor ise nextArama fonksiyonundan
    		sayac++;																					//arama yap�l�p ad�m say�s� d�nd�r�l�yor.
    		deger=hash_tablo[mod][1];
    		sonuc=nextArama(deger,mod,aranan,sayac);
    		printf("\nAranan de�er %d ad�mda bulundu.\n",sonuc);
    		return sonuc;
		}
		else{
			sayac++;
	  		sonuc=sayac;
	  		printf("\nAranan de�er %d ad�mda bulundu.\n",sonuc);
	  		return sonuc;
		}	  
	}
	else{
	  	printf("\nAranan de�er bulunamad�. L�tfen farkl� bir de�er ile deneyiniz.\n");
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
  	printf("\nSilmek istedi�iniz ki�inin numaras�n� giriniz: ");
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
		printf("\n|  ��LEM MEN�S�  |\n");
		printf("------------------\n");
		printf("| 1)M��teri Ekle |\n");
		printf("| 2)M��teri Ara  |\n");
		printf("| 3)M��teri Sil  |\n");
		printf("| 4)Hash Tablosu |\n");
		printf("| 5)Veri Listesi |\n");
		printf("------------------\n");
		printf("\nSe�iminiz: ");
		scanf("%d",&secim);

		switch(secim){	
			case 1:
				system("CLS");
				 klavyedenEkleme();
				 break;		 
			case 2:
				system("CLS");
				printf("\nArayaca��n�z m��terinin numaras�n� giriniz: ");
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

