#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_HOSTS 20
#define MAX_TEXT 1000
#define MAX_BINARY 10000
#define MAX_PACKETS 200
#define MAX_FRAMES 500
typedef struct
{
    char url[50];
    char ip[20];
    char mac[20];
}Host;

Host hosts[MAX_HOSTS];

int hostCount=0;

int choice;

/* Message */

char message[MAX_TEXT];

char binaryMessage[MAX_BINARY];

/* Packet Information */

int packetSize;

char packets[MAX_PACKETS][500];

int packetCount=0;

/* Frame Information */

int frameSize;

char frames[MAX_FRAMES][500];

int framePacketNumber[MAX_FRAMES];

int frameCount=0;

/* Source Destination */

char sourceURL[50];

char destinationURL[50];

int sourceIndex;

int destinationIndex;

/* Binary IP */

char sourceIPBinary[300];

char destinationIPBinary[300];

/* Binary MAC */

char sourceMACBinary[500];

char destinationMACBinary[500];

/* Port Numbers */

int sourcePort;
int destinationPort;

char sourcePortBinary[20];
char destinationPortBinary[20];


/********************************************************************
                FUNCTION DECLARATIONS
********************************************************************/

/* Host Table */

void initializeTable();

void displayTable();

void addHost();

void updateHost();

void deleteHost();

int findHost(char url[]);


/* File */

void writeFile();

void readFile();


/* Binary */

void charToBinary(unsigned char ch,char binary[]);

void textToBinary();


/* Packet */

void createPackets();

void displayPackets();


/* Frame */

void createFrames();

void displayFrames();


/* Address Conversion */

void ipToBinary();

void macToBinary();


/* Layers */

void applicationLayer();

void transportLayer();

void networkLayer();

void dataLinkLayer();

void physicalLayer();


/* Final Output */

void printTransmission();

void generatePorts();
void portToBinary(int port,char binary[]);
void printAll();


/********************************************************************
                        MAIN FUNCTION
********************************************************************/

int main()
{

    initializeTable();

    while(1)
    {
        printf("\n");
        printf("=====================================\n");
        printf("HOST TABLE MENU\n");
        printf("=====================================\n");

        printf("1.Display Host Table\n");
        printf("2.Add Host\n");
        printf("3.Update Host\n");
        printf("4.Delete Host\n");
        printf("5.Start Simulation\n");

        printf("\nEnter Choice : ");

        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                displayTable();

                break;

            case 2:

                addHost();

                break;

            case 3:

                updateHost();

                break;

            case 4:

                deleteHost();

                break;

            case 5:

                goto simulation;

            default:

                printf("\nInvalid Choice\n");
        }
    }

simulation:

    displayTable();

        writeFile();

        readFile();

        textToBinary();

        printf("\nEnter Packet Size (Bits) : ");
        scanf("%d",&packetSize);

        createPackets();

        displayPackets();

        printf("\nEnter Frame Size (Bits) : ");
        scanf("%d",&frameSize);

        createFrames();

        displayFrames();

        printf("\nEnter Source URL : ");
        scanf("%s",sourceURL);

        printf("Enter Destination URL : ");
        scanf("%s",destinationURL);

        sourceIndex=findHost(sourceURL);

        destinationIndex=findHost(destinationURL);

        ipToBinary();

        macToBinary();

        generatePorts();

        applicationLayer();

        transportLayer();

        networkLayer();

        dataLinkLayer();

        physicalLayer();

        printTransmission();
        printAll();

    return 0;
}
/********************************************************************
                    INITIALIZE HOST TABLE
********************************************************************/

void initializeTable()
{
    strcpy(hosts[0].url,"google.com");
    strcpy(hosts[0].ip,"142.250.183.14");
    strcpy(hosts[0].mac,"AA:BB:CC:11:22:33");

    strcpy(hosts[1].url,"youtube.com");
    strcpy(hosts[1].ip,"142.250.196.46");
    strcpy(hosts[1].mac,"44:55:66:77:88:99");

    strcpy(hosts[2].url,"facebook.com");
    strcpy(hosts[2].ip,"157.240.22.35");
    strcpy(hosts[2].mac,"10:20:30:40:50:60");

    strcpy(hosts[3].url,"college.edu");
    strcpy(hosts[3].ip,"192.168.1.20");
    strcpy(hosts[3].mac,"12:34:56:78:9A:BC");

    strcpy(hosts[4].url,"server.com");
    strcpy(hosts[4].ip,"10.10.10.10");
    strcpy(hosts[4].mac,"AB:CD:EF:12:34:56");

    hostCount=5;
}

/********************************************************************
                    DISPLAY HOST TABLE
********************************************************************/

void displayTable()
{
    int i;

    printf("\n");
    printf("=====================================================================\n");
    printf("                         HOST TABLE\n");
    printf("=====================================================================\n");

    printf("%-5s %-20s %-18s %-20s\n",
           "No",
           "URL",
           "IP Address",
           "MAC Address");

    printf("---------------------------------------------------------------------\n");

    for(i=0;i<hostCount;i++)
    {
        printf("%-5d %-20s %-18s %-20s\n",
               i+1,
               hosts[i].url,
               hosts[i].ip,
               hosts[i].mac);
    }

    printf("=====================================================================\n");
}

/********************************************************************
            CONVERT PORT NUMBER TO 16-BIT BINARY
********************************************************************/

void portToBinary(int port,char binary[])
{
    int i;

    for(i=15;i>=0;i--)
    {
        if((port>>i)&1)
        {
            binary[15-i]='1';
        }
        else
        {
            binary[15-i]='0';
        }
    }

    binary[16]='\0';
}
/********************************************************************
                GENERATE RANDOM PORT NUMBERS
********************************************************************/

void generatePorts()
{
    srand(time(NULL));

    sourcePort=1024+rand()%64512;
    destinationPort=1024+rand()%64512;

    portToBinary(sourcePort,sourcePortBinary);
    portToBinary(destinationPort,destinationPortBinary);
}
/********************************************************************
                        ADD HOST
********************************************************************/

void addHost()
{
    if(hostCount>=MAX_HOSTS)
    {
        printf("\nHost Table Full\n");
        return;
    }

    printf("\nEnter URL : ");
    scanf("%s",hosts[hostCount].url);

    printf("Enter IP Address : ");
    scanf("%s",hosts[hostCount].ip);

    printf("Enter MAC Address : ");
    scanf("%s",hosts[hostCount].mac);

    hostCount++;

    printf("\nHost Added Successfully.\n");
}

/********************************************************************
                    UPDATE HOST
********************************************************************/

void updateHost()
{
    char url[50];

    int index;

    printf("\nEnter URL to Update : ");
    scanf("%s",url);

    index=findHost(url);

    if(index==-1)
    {
        printf("\nHost Not Found\n");
        return;
    }

    printf("\nEnter New URL : ");
    scanf("%s",hosts[index].url);

    printf("Enter New IP : ");
    scanf("%s",hosts[index].ip);

    printf("Enter New MAC : ");
    scanf("%s",hosts[index].mac);

    printf("\nHost Updated Successfully\n");
}

/********************************************************************
                    DELETE HOST
********************************************************************/

void deleteHost()
{
    char url[50];

    int index;

    int i;

    printf("\nEnter URL to Delete : ");
    scanf("%s",url);

    index=findHost(url);

    if(index==-1)
    {
        printf("\nHost Not Found\n");
        return;
    }

    for(i=index;i<hostCount-1;i++)
    {
        hosts[i]=hosts[i+1];
    }

    hostCount--;

    printf("\nHost Deleted Successfully\n");
}

/********************************************************************
                        FIND HOST
********************************************************************/

int findHost(char url[])
{
    int i;

    for(i=0;i<hostCount;i++)
    {
        if(strcmp(hosts[i].url,url)==0)
        {
            return i;
        }
    }

    return -1;
}

/********************************************************************
                WRITE MESSAGE TO FILE
********************************************************************/

void writeFile()
{
    FILE *fp;

    int ch;

    fp=fopen("message.txt","w");

    if(fp==NULL)
    {
        printf("\nCannot Create File\n");
        exit(0);
    }

    printf("\nEnter Message : ");

    while((ch=getchar())!='\n' && ch!=EOF);

    fgets(message,MAX_TEXT,stdin);

    fputs(message,fp);

    fclose(fp);

    printf("\nMessage Written Successfully.\n");
}

/********************************************************************
                READ MESSAGE FROM FILE
********************************************************************/

void readFile()
{
    FILE *fp;

    fp=fopen("message.txt","r");

    if(fp==NULL)
    {
        printf("\nCannot Open File\n");
        exit(0);
    }

    fgets(message,MAX_TEXT,fp);

    fclose(fp);

    printf("\n");
    printf("=========================================\n");
    printf("MESSAGE READ FROM FILE\n");
    printf("=========================================\n");

    printf("%s\n",message);
}
/********************************************************************
            CONVERT ONE CHARACTER TO BINARY
********************************************************************/

void charToBinary(unsigned char ch,char binary[])
{
    int i;

    for(i=7;i>=0;i--)
    {
        if((ch>>i)&1)
        {
            binary[7-i]='1';
        }
        else
        {
            binary[7-i]='0';
        }
    }

    binary[8]='\0';
}

/********************************************************************
            CONVERT COMPLETE MESSAGE TO BINARY
********************************************************************/

void textToBinary()
{
    int i;
    int len;

    char temp[9];

    binaryMessage[0]='\0';

    printf("\n");
    printf("=========================================\n");
    printf("BINARY CONVERSION\n");
    printf("=========================================\n");

    for(i=0;message[i]!='\0';i++)
    {
        if(message[i]=='\n')
        {
            continue;
        }

        charToBinary(message[i],temp);

        printf("%c --> %s\n",message[i],temp);

        strcat(binaryMessage,temp);
    }

    printf("\nComplete Binary Message\n\n");

    printf("%s\n",binaryMessage);

    len=strlen(binaryMessage);

    printf("\nBinary Length : %d Bits\n",len);
}

/********************************************************************
                CREATE PACKETS
********************************************************************/

/********************************************************************
                    CREATE PACKETS
********************************************************************/

/********************************************************************
                    CREATE PACKETS
********************************************************************/
/********************************************************************
                    CREATE PACKETS
********************************************************************/

void createPackets()
{
    int i;
    int j;
    int length;

    packetCount=0;

    length=strlen(binaryMessage);

    for(i=0;i<length;i=i+packetSize)
    {
        for(j=0;j<packetSize;j++)
        {
            if((i+j)<length)
            {
                packets[packetCount][j]=binaryMessage[i+j];
            }
            else
            {
                packets[packetCount][j]='0';      // Padding Zero
            }
        }

        packets[packetCount][packetSize]='\0';

        packetCount++;
    }
}


/********************************************************************
                DISPLAY PACKETS
********************************************************************/

void displayPackets()
{
    int i;

    printf("\n");

    printf("=========================================\n");
    printf("PACKET CREATION\n");
    printf("=========================================\n");

    printf("\nPacket Size : %d Bits\n",packetSize);

    printf("Total Packets : %d\n\n",packetCount);

    for(i=0;i<packetCount;i++)
    {
        printf("-----------------------------------------\n");

        printf("Packet %d\n",i+1);

        printf("-----------------------------------------\n");

        printf("%s\n",packets[i]);

        printf("\n");
    }
}

void createFrames()
{
    int i;
    int j;
    int k;
    int length;

    frameCount=0;

    for(i=0;i<packetCount;i++)
    {
        length=strlen(packets[i]);

        for(j=0;j<length;j=j+frameSize)
        {
            for(k=0;k<frameSize;k++)
            {
                if((j+k)<length)
                {
                    frames[frameCount][k]=packets[i][j+k];
                }
                else
                {
                    frames[frameCount][k]='0';    // Padding Zero
                }
            }

            frames[frameCount][frameSize]='\0';

            framePacketNumber[frameCount]=i+1;

            frameCount++;
        }
    }
}

void displayFrames()
{
    int i;
    int currentPacket=0;

    printf("\n");
    printf("=========================================\n");
    printf("FRAME CREATION\n");
    printf("=========================================\n");

    printf("\nFrame Size : %d Bits\n",frameSize);

    printf("Total Frames : %d\n\n",frameCount);

    for(i=0;i<frameCount;i++)
    {
        if(framePacketNumber[i]!=currentPacket)
        {
            currentPacket=framePacketNumber[i];

            printf("-----------------------------------------\n");
            printf("PACKET %d\n",currentPacket);
            printf("-----------------------------------------\n");
        }

        printf("Frame %d : %s\n",i+1,frames[i]);
    }
}

void ipToBinary()
{
    char temp[30];
    char *token;
    char oneByte[9];

    int number;

    sourceIPBinary[0]='\0';
    destinationIPBinary[0]='\0';

    /* Source IP */

    strcpy(temp,hosts[sourceIndex].ip);

    token=strtok(temp,".");

    while(token!=NULL)
    {
        number=atoi(token);

        charToBinary((unsigned char)number,oneByte);

        strcat(sourceIPBinary,oneByte);
        strcat(sourceIPBinary," ");

        token=strtok(NULL,".");
    }

    /* Destination IP */

    strcpy(temp,hosts[destinationIndex].ip);

    token=strtok(temp,".");

    while(token!=NULL)
    {
        number=atoi(token);

        charToBinary((unsigned char)number,oneByte);

        strcat(destinationIPBinary,oneByte);
        strcat(destinationIPBinary," ");

        token=strtok(NULL,".");
    }
}

/********************************************************************
                CONVERT MAC ADDRESS TO BINARY
********************************************************************/

void macToBinary()
{
    char temp[30];
    char *token;
    char oneByte[9];

    int number;

    sourceMACBinary[0]='\0';
    destinationMACBinary[0]='\0';

    /* Source MAC */

    strcpy(temp,hosts[sourceIndex].mac);

    token=strtok(temp,":");

    while(token!=NULL)
    {
        number=(int)strtol(token,NULL,16);

        charToBinary((unsigned char)number,oneByte);

        strcat(sourceMACBinary,oneByte);
        strcat(sourceMACBinary," ");

        token=strtok(NULL,":");
    }

    /* Destination MAC */

    strcpy(temp,hosts[destinationIndex].mac);

    token=strtok(temp,":");

    while(token!=NULL)
    {
        number=(int)strtol(token,NULL,16);

        charToBinary((unsigned char)number,oneByte);

        strcat(destinationMACBinary,oneByte);
        strcat(destinationMACBinary," ");

        token=strtok(NULL,":");
    }
}
/********************************************************************
                    APPLICATION LAYER
********************************************************************/

void applicationLayer()
{
    int len;

    printf("\n");
    printf("=====================================================\n");
    printf("                APPLICATION LAYER\n");
    printf("=====================================================\n");

    printf("\nOriginal Message\n\n");

    printf("%s",message);

    len=strlen(message);

    if(len>0 && message[len-1]=='\n')
    {
        len--;
    }

    printf("\nCharacters : %d\n",len);
}

/********************************************************************
                    TRANSPORT LAYER
********************************************************************/

void transportLayer()
{
    int i;

    printf("\n");
    printf("=====================================================\n");
    printf("                 TRANSPORT LAYER\n");
    printf("=====================================================\n");

    printf("\nBinary Message\n\n");

    printf("%s\n",binaryMessage);
        printf("\n");
        printf("Source Port Number : %d\n",sourcePort);

        printf("Destination Port Number : %d\n",destinationPort);

        printf("\nSource Port (Binary)\n");
        printf("%s\n",sourcePortBinary);

        printf("\nDestination Port (Binary)\n");
        printf("%s\n",destinationPortBinary);

    printf("\nBinary Length : %d Bits\n",(int)strlen(binaryMessage));

    printf("\nPacket Size : %d Bits\n",packetSize);

    printf("Total Packets : %d\n\n",packetCount);

    for(i=0;i<packetCount;i++)
    {
        printf("-----------------------------------------\n");
        printf("Packet %d\n",i+1);
        printf("-----------------------------------------\n");
        printf("%s\n",packets[i]);
        printf("\n");
    }
}

/********************************************************************
                    NETWORK LAYER
********************************************************************/

void networkLayer()
{
    printf("\n");
    printf("=====================================================\n");
    printf("                  NETWORK LAYER\n");
    printf("=====================================================\n");

    printf("\nSource URL\n");
    printf("%s\n",hosts[sourceIndex].url);

    printf("\nDestination URL\n");
    printf("%s\n",hosts[destinationIndex].url);

    printf("\nSource IP\n");
    printf("%s\n",hosts[sourceIndex].ip);

    printf("\nDestination IP\n");
    printf("%s\n",hosts[destinationIndex].ip);

    printf("\nSource IP (Binary)\n");
    printf("%s\n",sourceIPBinary);

    printf("\nDestination IP (Binary)\n");
    printf("%s\n",destinationIPBinary);
}

/********************************************************************
                    DATA LINK LAYER
********************************************************************/

void dataLinkLayer()
{
    int i;
    int currentPacket=0;

    printf("\n");
    printf("=====================================================\n");
    printf("                DATA LINK LAYER\n");
    printf("=====================================================\n");

    printf("\nFrame Size : %d Bits\n",frameSize);

    printf("Total Frames : %d\n",frameCount);

    printf("\nSource MAC\n");
    printf("%s\n",hosts[sourceIndex].mac);

    printf("\nDestination MAC\n");
    printf("%s\n",hosts[destinationIndex].mac);

    printf("\nSource MAC (Binary)\n");
    printf("%s\n",sourceMACBinary);

    printf("\nDestination MAC (Binary)\n");
    printf("%s\n",destinationMACBinary);

    printf("\n");

    for(i=0;i<frameCount;i++)
    {
        if(framePacketNumber[i]!=currentPacket)
        {
            currentPacket=framePacketNumber[i];

            printf("-----------------------------------------\n");
            printf("PACKET %d\n",currentPacket);
            printf("-----------------------------------------\n");
        }

        printf("Frame %d : %s\n",i+1,frames[i]);
    }
}

/********************************************************************
                    PHYSICAL LAYER
********************************************************************/

void physicalLayer()
{
    printf("\n");
    printf("=====================================================\n");
    printf("                PHYSICAL LAYER\n");
    printf("=====================================================\n");

    printf("\nPacket Transmission Started...\n");

    printf("\nPacket Size : %d Bits\n",packetSize);

    printf("Frame Size : %d Bits\n",frameSize);

    printf("Total Packets : %d\n",packetCount);

    printf("Total Frames : %d\n",frameCount);

    printf("\nFrames are Ready for Transmission...\n");
}

/********************************************************************
                FINAL TRANSMISSION
********************************************************************/
/********************************************************************
                FINAL TRANSMISSION
********************************************************************/

void printTransmission()
{
    int i;
    int currentPacket=0;

    printf("\n");
    printf("=============================================================\n");
    printf("             FINAL FRAME TRANSMISSION\n");
    printf("=============================================================\n");

    for(i=0;i<frameCount;i++)
    {
        if(framePacketNumber[i]!=currentPacket)
        {
            currentPacket=framePacketNumber[i];

            printf("\n");
            printf("#############################################################\n");
            printf("                     PACKET %d\n",currentPacket);
            printf("#############################################################\n");
        }

        printf("\n");
        printf("---------------------- FRAME %d ----------------------\n",i+1);

        printf("\nHEADER\n");

        printf("\nSource URL\n");
        printf("%s\n",hosts[sourceIndex].url);

        printf("\nDestination URL\n");
        printf("%s\n",hosts[destinationIndex].url);

        printf("\nSource IP\n");
        printf("%s\n",hosts[sourceIndex].ip);

        printf("\nDestination IP\n");
        printf("%s\n",hosts[destinationIndex].ip);

        printf("\nSource MAC\n");
        printf("%s\n",hosts[sourceIndex].mac);

        printf("\nDestination MAC\n");
        printf("%s\n",hosts[destinationIndex].mac);

        printf("\nSource IP (Binary)\n");
        printf("%s\n",sourceIPBinary);

        printf("\nDestination IP (Binary)\n");
        printf("%s\n",destinationIPBinary);

        printf("\nSource MAC (Binary)\n");
        printf("%s\n",sourceMACBinary);

        printf("\nDestination MAC (Binary)\n");
        printf("%s\n",destinationMACBinary);

        printf("\nPacket Number\n");
        printf("%d\n",framePacketNumber[i]);

        printf("\nPayload\n");
        printf("%s\n",frames[i]);

        printf("\nTrailer\n");
        printf("00000000\n");

        printf("\n------------------------------------------------------\n");
    }

    printf("\n=============================================================\n");
    printf("      ALL FRAMES TRANSMITTED SUCCESSFULLY\n");
    printf("=============================================================\n");
}
void printAll()
{
        int i;
    int currentPacket=0;

    printf("\n");
    printf("=============================================================\n");
    printf("             FINAL FRAME TRANSMISSION\n");
    printf("=============================================================\n");

    for(i=0;i<frameCount;i++)
    {
        if(framePacketNumber[i]!=currentPacket)
        {
            currentPacket=framePacketNumber[i];

            printf("\n");
            printf("#############################################################\n");
            printf("                     PACKET %d\n",currentPacket);
            printf("#############################################################\n");
        }
                printf("\nPacket Number\n");
        printf("%d\n",framePacketNumber[i]);

        printf("\n");
        printf("---------------------- FRAME %d ----------------------\n",i+1);




        printf("%s\t",sourceIPBinary);


        printf("%s\t",destinationIPBinary);


        printf("%s\t",sourceMACBinary);


        printf("%s\t",destinationMACBinary);

                printf("%s\n",sourcePortBinary);

        printf("%s\n",destinationPortBinary);


        printf("%s\t",frames[i]);


        printf("00000000\n");

        printf("\n------------------------------------------------------\n");
    }

    printf("\n=============================================================\n");
    printf("      ALL FRAMES TRANSMITTED SUCCESSFULLY\n");
    printf("=============================================================\n");
}
