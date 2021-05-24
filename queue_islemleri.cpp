#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct kuyrukVeriYapisi
{ 
	int oncelik;
	char isim[30];
	struct kuyrukVeriYapisi *sonraki;
};

kuyrukVeriYapisi *ilk=NULL,*son=NULL,*gecici=NULL;

void dosyadanOku(FILE *dosya){  									 //Dosyadan okunan verilerin sýralý olduðu kabul edilerek iþlem yapýlýyor
	while(!feof(dosya)){	
		gecici=(kuyrukVeriYapisi*)malloc(sizeof(kuyrukVeriYapisi));  //Dinamik olarak yer açýlýyor
		gecici->sonraki=NULL;
		fscanf(dosya,"%d %s",&gecici->oncelik,&gecici->isim);		 //Öncelik isim formatýna uygun okuma yapýlýyor
		if(ilk==NULL){												 //Eðer kuyruk boþsa ilk olarak baþa ekleniyor
			ilk=gecici;
			son=ilk;
		}
		else{														 //Kuyrukta eleman varsa sona ekleme yapýlýyor
			son->sonraki=gecici;
			son=gecici;
		}
	}
}

void listele(){                                                       //Kuyruðun baþýndan sonuna kadar sýrayla gezilip öncelik-isim formatýna göre ekrana yazdýrýlýyor
	printf("\n");
	gecici=ilk;
	printf(" ÖNCELÝK | ÝSÝM\n");
	while(gecici!=NULL)
	{
		printf("    %d      %s\n",gecici->oncelik,gecici->isim);
		gecici=gecici->sonraki;
	}
	return ;
}

void klavyedenEkle()											 	  					//Kullanýcýnýn klavyeden girdiði verilere göre iþlem yapýlýp uygun yerlere ekleme yapýlýyor. 
{																	  					//Hali hazýrda dosyadan kayýt alýndýðý için kuyruðun boþ olmadýðý varsayýlýyor.		
	kuyrukVeriYapisi *eklenecek=(kuyrukVeriYapisi*)malloc(sizeof(kuyrukVeriYapisi));	//Yeni kayýt için dinamik olarak yer açýlýyor
	eklenecek->sonraki=NULL;
	fflush(stdin);																		//Klavyeden giriþ hatasýný engellemek için input temizleniyor.
	printf("\nÖncelik giriniz ->");
	scanf("%d",&eklenecek->oncelik);
	fflush(stdin);
	printf("\nÝsim giriniz ->");
	scanf("%s",&eklenecek->isim);
	gecici=ilk;
	int eklendi = 0;																	//Ekleme yapýlýp yapýlmadýðýný belirten bayrak.
	while(gecici->sonraki!=NULL){
		if(gecici->oncelik <= eklenecek->oncelik && eklenecek->oncelik < gecici->sonraki->oncelik){  //Yeni kaydýn önceliði diðer kayýtlar ile karþýlaþtýrýlýp uygun yere ekleme yapýlýyor.
			eklenecek->sonraki=gecici->sonraki;
			gecici->sonraki=eklenecek;
			eklendi = 1;																//Ekleme bayraðý 1 yapýlýyor.
			break;
		}
		gecici=gecici->sonraki;
	}
	if(eklendi==0){																		//Ekleme bayraðý 1 deðilse ekleme yapýlamamýþtýr. Kaydýn önceliði daha önce eklenmiþ bir öncelik seviyesi
		gecici->sonraki=eklenecek;														//deðildir. Dolayýsýyla sona ekleme yapýlýyor.
		eklenecek->sonraki=NULL;
	}
}

int siraBul(char *arananKayit)															//Kullanýcýnýn klavyeden girdiði kayýt ismine göre arama yapýlýyor.
{
	int sayac=0;
	gecici=ilk;
	while(gecici!=NULL)
	{
		if(!strcmp(strupr(arananKayit),strupr(gecici->isim)))							//strcmp fonksiyonu ile karþýlaþtýrma yapýlýyor. strupr fonksiyonunun kullanýlma amacý kayýtlarý büyük harfe çevirip
		{																				//büyük küçük harf farklýlýðýný önlemek. strupr yerine strlwr de kullanýlabilir. Kayýtlarýn ilk aramadan sonra 
			return sayac;																//büyük harfe geçmesinin sebebi bu fonksiyon.
		}
		else
		{
			sayac++;
			gecici=gecici->sonraki;
		}
	}
	return -1;
}
	
int main(){	
	setlocale(LC_ALL,"Turkish");					//Türkçe karakterleri kullanabilmek için lokal dil seçeneði.
    FILE *dosya = fopen("kayitlar.txt","r");
	dosyadanOku(dosya);
	fclose(dosya);
	int secim;
	while(1)
	{	
		printf("\n1.)LÝSTELE \n2.)KAYIT EKLE\n3.)SIRA BUL\n4.)PROGRAMI SONLANDIR...\n\nLütfen seçim yapýnýz -> ");
		scanf("%d",&secim);
		switch (secim)
		{
	    	case 1:
		  	{
				if(ilk==NULL){
					printf("\nListe boþ. Lütfen kayýt ekleyiniz...\n");
					printf("\nDevam etmek için bir tuþa basýnýz.\n");
					getch();
					system("CLS");
					break;	
				}else{
					listele();
					printf("\nDevam etmek için bir tuþa basýnýz.\n");
					getch();
					system("CLS");
					break;
				} 
			}
			
	    	case 2:
		  	{
			  	klavyedenEkle();
				printf("\nEkleme tamamlandý.\n");
				printf("\nDevam etmek için bir tuþa basýnýz.\n");
				getch();
				system("CLS");
			  	break;
		  	}
			  	 
	      	case 3:
		  	{
				char arananKayit[20];
				printf("\nAradýðýnýz kaydýn ismini giriniz ->\n");
				scanf("%s",arananKayit);
				int sira = siraBul(arananKayit);
				if(sira==-1){
					printf("Aradýðýnýz isimde kayýt bulunamamýþtýr.\n");
					printf("\nDevam etmek için bir tuþa basýnýz.\n");
					getch();
					system("CLS");
					break;
				}
				else{
					printf("\nAradýðýnýz kaydýn önünde %d kiþi var.\n",sira);
					printf("\nDevam etmek için bir tuþa basýnýz.\n");
					getch();
					system("CLS");
					break;
				}
		  	}
		  	
	      	case 4:
	      	{
		  		printf("\nPROGRAM SONLANDIRILIYOR\n");
		  		exit(0);
		  		break;
		  	}
		  	
	      	default:
			{
			printf("\nYANLIÞ SEÇÝM YAPTINIZ. LÜTFEN 1 - 4 ARASI SEÇÝM YAPINIZ!!!\n");
			printf("\nDevam etmek için bir tuþa basýnýz.\n");
			getch();
			system("CLS");
			break;
			}
		}
	}
	return 0;
}








