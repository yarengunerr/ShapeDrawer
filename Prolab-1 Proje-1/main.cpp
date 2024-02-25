#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <graphics.h>
#include <string.h>


#define maxCizgiBoyutu 256
#define maxKoordinat 10



void arkaPlanCiz(int x1, int y1, int x2, int y2, int renk)
 {
    setcolor(renk);
    line(x1, y1, x2, y2);
 }

int main() {
    CURL *curl;
    CURLcode sonuc;
    FILE *dosyaVerisi;
   char url[] = "http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";
    char dosyaAdi[] = "Koordinatlar.txt";

    printf("Koordinatlar basariyla deneme.txt dosyasina kaydedildi.\n");
    
    int hangiSatir;
    printf("Hangi satirdaki koordinatlari cizmemi istersin? (1B=1 ve 2B=2)\n");
    scanf("%d", &hangiSatir);    
    
    	initwindow(1500,1500,"BGI Penceresi 1");
		
		int x=0;
		int y=0;
		for(x=0;x<1500;x+=10)//birim kare deðil de 10a 10luk kareler yaptýk en son alan hesabýndan sonra 100e bölücez
		{
			setcolor(15);
			setlinestyle(0,1,0);
			line(0,x,1500,x);	
		}
			for(y=0;y<1500;y+=10)
		{
			setcolor(15);
			setlinestyle(0,1,0);
			line(y,0,y,1500);	
		} 
		

 FILE *dosya;
    char line[maxCizgiBoyutu];
    int satir1[maxKoordinat][2];
    int satir2[maxKoordinat][2];
    int koordinatSayaci1 = 0;
    int koordinatSayaci2 = 0;

    dosya = fopen("Koordinatlar.txt", "r");
    if (dosya == NULL)
	{
        perror("Dosya acma hatasi");
        return 1;
    }

    int sayac = 1;
    int (*yeniKoordinat)[2];
    int *yeniKoordinatSayaci;

    while (fgets(line, maxCizgiBoyutu, dosya) != NULL)
	 {
        if (strstr(line, "B(") != NULL && strstr(line, ")F") != NULL)
		 {
            char *koordinatIkilisi = strtok(line, "(");  
            yeniKoordinat = (sayac == 1) ? satir1 : satir2;
            yeniKoordinatSayaci = (sayac == 1) ? &koordinatSayaci1 : &koordinatSayaci2;
            printf("%d. satir (", sayac);

            while ((koordinatIkilisi = strtok(NULL, "(, )")) != NULL) 
			{
                yeniKoordinat[*yeniKoordinatSayaci][0] = atoi(koordinatIkilisi);
                koordinatIkilisi = strtok(NULL, "(, )");
                if (koordinatIkilisi != NULL) 
			{
                 yeniKoordinat[*yeniKoordinatSayaci][1] = atoi(koordinatIkilisi);
                    printf("(%d,%d)", yeniKoordinat[*yeniKoordinatSayaci][0], yeniKoordinat[*yeniKoordinatSayaci][1]);
                    if (koordinatIkilisi != NULL)
					{
                        printf(" ");
                    }
                    (*yeniKoordinatSayaci)++;
            }
            }
            printf(")\n");
            sayac++;
        }
    }

    fclose(dosya);

    printf("\n\ndizi1:\n");
    yeniKoordinat = satir1;
    yeniKoordinatSayaci = &koordinatSayaci1;
    for (int i = 0; i < *yeniKoordinatSayaci; i++) {
        printf("%d,%d,", yeniKoordinat[i][0], yeniKoordinat[i][1]);
    }

    printf("\n\ndizi2:\n");
    yeniKoordinat = satir2;
    yeniKoordinatSayaci = &koordinatSayaci2;
    for (int i = 0; i < *yeniKoordinatSayaci; i++) {
        printf("%d,%d,", yeniKoordinat[i][0], yeniKoordinat[i][1]);
    }

    int satir1_carpilmis[maxKoordinat][2];
    int satir2_carpilmis[maxKoordinat][2];
    for (int i = 0; i < koordinatSayaci1; i++)
	 {
        satir1_carpilmis[i][0] = satir1[i][0] * 10;
        satir1_carpilmis[i][1] = satir1[i][1] * 10;
    }
    for (int i = 0; i < koordinatSayaci2; i++) 
	{
        satir2_carpilmis[i][0] = satir2[i][0] * 10;
        satir2_carpilmis[i][1] = satir2[i][1] * 10;
    }

    int elemanSayisiDizi1 = sizeof(satir1_carpilmis) / sizeof(satir1_carpilmis[0]);
    int elemanSayisiDizi2 = sizeof(satir2_carpilmis) / sizeof(satir2_carpilmis[0]);

		int a=elemanSayisiDizi1/2;
		int b=elemanSayisiDizi2/2;

		if(hangiSatir==1)
		{
		
    setfillstyle(1, 1);
    fillpoly(a, &satir1_carpilmis[0][0]);

    int pikselSayisi = 0;
    for (int x = 0; x < getmaxx(); x++) 
	{
        for (int y = 0; y < getmaxy(); y++)
		 {
            int renk = getpixel(x, y);
            if (renk == 1)
		    {
                pikselSayisi++;
            }
        }
    }
    int sekil1Alani=pikselSayisi/100;//baþta kareleri 10la çarptýðýmýz için alan için 100e bölüyoruz
    printf("\n\nDoldurulan alan piksel sayisi: %d\n", sekil1Alani);
    
    int rezervDegeri1=sekil1Alani*10;
    printf("1.seklin rezerv degeri %d\n", rezervDegeri1);

		}
		 
		else if (hangiSatir == 2) 
		{
   
    setfillstyle(1, 2);
    fillpoly(b, &satir2_carpilmis[0][0]);

    setfillstyle(1, 5);
    fillpoly(b, &satir2_carpilmis[b][0]);   
   
    int pikselSayisi2 = 0;
    for (int x = 0; x < getmaxx(); x++)
	{
        for (int y = 0; y < getmaxy(); y++) 
		{
            int renk = getpixel(x, y);
            if (renk == 2)
		    {
                pikselSayisi2++;
            }
        }
    }
    int sekil2Alani = pikselSayisi2 / 100;
    printf("\n\nDoldurulan alan piksel sayisi2: %d\n", sekil2Alani);

    int rezervDegeri2 = sekil2Alani * 10;
    printf("1.seklin rezerv degeri %d\n", rezervDegeri2);
  
    int pikselSayisi3 = 0;
    for (int x = 0; x < getmaxx(); x++)
	{
        for (int y = 0; y < getmaxy(); y++)
	    {
            int renk = getpixel(x, y);
            if (renk == 5)
		    {
                pikselSayisi3++;
            }
        }
    }
    int sekil3Alani = pikselSayisi3 / 100;
    printf("\nDoldurulan alan piksel sayisi: %d\n", sekil3Alani);

    int rezervDegeri3 = sekil3Alani * 10;
    printf("2.seklin rezerv degeri %d\n", rezervDegeri3);
        }
		
	    delay(5000);
		closegraph();
		////////2.aþama
			initwindow(1500,1500,"BGI Penceresi 2");
            int x1, y1,j;
   
    printf("\n\nMaliyet kac olsun? (lutfen 1-10 arasi bir deger girin)\n");
    scanf("%d",&j); 
    
       int k=11-j;  //j deðeri ne kadar büyük olursa kareler o kadar büyük oluyor, kareler az olursa maliyet de az olur yani karenin büyük olmasý maliyet az demek
                   //o zaman maliyet deðeri ile karelerin büyüklüðü ters orantýlý olmalý
    for (x1 = 0; x1 < 1500; x1 += (10 * k)) 
	{
        for (y1 = 0; y1 < 1500; y1 += (10 * k))
		 {
            arkaPlanCiz(x1, y1, x1 + (10 * k), y1, 2);
            arkaPlanCiz(x1, y1, x1, y1 + (10 * k), 2);
        }
    }
			if(hangiSatir==1)
			{
    setcolor(WHITE);
    drawpoly(a, &satir1_carpilmis[0][0]);
		    }
		 
		else if (hangiSatir == 2)
		 {
       setcolor(WHITE);
       drawpoly(b, &satir2_carpilmis[0][0]);
       drawpoly(b, &satir2_carpilmis[b][0]);   
        }
        delay(50000);
		closegraph();
		}
		
