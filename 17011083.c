#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Harflerin sıklığı ve harfin kendisi, linkli-liste'de tutuluyor.
struct harfSiklik
{
	int freq; //siklik
	char harf; //harf
	struct harfSiklik* next;
};

struct harfSiklik* head=NULL;

//Bir Huffman Tree tanımladık. 
struct MinHeapNode 
{ 
    char harf;
    int freq; 
    struct MinHeapNode *left, *right, *next; 
};

struct MinHeapNode* GetNewNode(int freq, char harf);
struct MinHeapNode* Insert(struct MinHeapNode* root, int freq, char harf);
bool Search(struct MinHeapNode* root, int freq, char harf);

struct MinHeapNode* root = NULL;

int main(void)
{
	//Sikistirilacak yazi kullanıcıdan alınır.
	char yazi[1000], tempYazi[1000];
	printf("Sikistirilacak yaziyi giriniz: \n");
	//scanf("%s", yazi);
	gets(tempYazi);
	printf("\nGirilen yazi: %s", tempYazi);
	
	//Kaç tane harf girildiğinin sayısı count'ta tutuluyor.
	int j=0, count=0, d=0;
	while(tempYazi[j] != '\0')
	{
		if(!(tempYazi[j] == ' '))
		{
			yazi[d]=tempYazi[j];
			d++;
			count++; //50 tane karakter girdim. aaabbbaactydshdsjaaajhbb. 5 farklı
		}
		//printf("\nCount: %d", count);
		//printf(" %c", yazi[j]);
		j++;
	}
	yazi[d] = '\0';
	
	printf("\nCount: %d", count);
	
	//Farkli değerlerin yer alacağı dizi.
	char farkliHarflerDizisi[29];
	int i;
	for(i=0; i<29; i++)
	{
		farkliHarflerDizisi[i]='\0';
		//printf(" %s", farkliHarflerDizisi[i]); returns NULL
	}	
	
	printf("\n");
	
	//Kaç tane farklı harfin olduğunun sayısı countFarkli'da tutulacak.
	int countFarkli=0, k, isFarkli;
	for(j=0; j<count; j++)
	{
		printf("Yazi: ");
		printf(" %c\n", yazi[j]);
		isFarkli=1;
		for(k=0; k<j; k++)
		{
			if(yazi[j] == farkliHarflerDizisi[k]) //eşitse
			{
				isFarkli=0;
			}
		}
		//Eğer hiç eşit bulamamışsak...
		if(isFarkli==1)
		{
			farkliHarflerDizisi[countFarkli]=yazi[j];
			printf("Farkli harfler: ");
			printf(" %c\n", farkliHarflerDizisi[countFarkli]);
			countFarkli++;
		}
	}
	printf("countfarkli: %d\n", countFarkli); //4
	
	//Array of structs.
	//struct harfSiklik* head = NULL;
	
	//Struct dizisinin her bir değerine, farklı bir harfi atadık.
	for(i=0; i<countFarkli; i++)
		push(&head, 0, farkliHarflerDizisi[i]);
	
	//Frekans bulunur.
	char s=yazi[0];
	i=0;
	int indis=0, belirtec;
	while(s!='\0')
	{
		//O harfin bulunduğu struct'ın sahip olduğu 'freq' değerini set et.
		struct harfSiklik* current=head;
		//printf("%d %c\n", current->freq, current->harf);
		while (current!=NULL && current->harf!=s) 
		{
			current=current->next;
		}
		if(current->harf==s)
		{ 
			//printf("%d %c\n", current->freq, current->harf);
			current->freq=(current->freq)+1;
		}
		//printf("s: %c\n", s);
		indis++;
		s=yazi[indis];
	}
	
	//Ekrana yazdirilir.
	struct harfSiklik* current=head;
	while(current!=NULL)
	{
		printf("%d %c\n", current->freq, current->harf);
		current=current->next;
	}
	
	//Insertion Sort
	insertionSort(&head); 
	
	//Printing
	current=head;
	while(current!=NULL)
	{
		printf("\n%d %c", current->freq, current->harf);
		current=current->next;
	}
	
	//Ağaç oluşturma
	printf("\nAgac olusturma\n");
	//struct MinHeapNode* root;
	//root = NULL;
	int isLast=0;
	current=head;
	while(current!=NULL)
	{
		printf("\nAgac olusturuluyor.");
		
		current=head;
		
		//printf("\n\n %c %c", current->harf, current->next->harf);
		if(current->harf == '\0' && current->next->harf == '\0')
		{
			isLast=1;
		}
		//printf("\nisLast: %d", isLast);
		if(isLast==1) //ikisinin de harfi yoksa
		{
			//deleteNode(&head, 1);
			//printf("\ncurrent->next->freq: %d", current->next->freq);
		}
		
		//Bir tane minHeapNode oluşturduk.
		struct MinHeapNode* temp;
		temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
		
		//Şu anki harfSiklik'un freq değeri ile bir sonraki harfSiklik'un freq değerinin toplamını temp->freq değerine ata.
		temp->freq = current->freq + current->next->freq;
		temp->harf = '\0';
		
		//Node'un soluna yeni bir harfSiklik ata.
		struct MinHeapNode* tempLeft;
		tempLeft = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
		temp->left = tempLeft;
		temp->left->freq = current->freq;
		temp->left->harf = current->harf;
		
		//Node'un sağına yeni bir harfSiklik ata.
		struct MinHeapNode* tempRight;
		tempRight = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
		temp->right = tempRight;
		temp->right->freq=current->next->freq;
		temp->right->harf=current->next->harf;
		
		//Printing the tree
		//printf("\n%d %c", temp->freq, temp->harf);
		//printf("\n%d%c", temp->left->freq, temp->left->harf);
		//printf(" %d%c", temp->right->freq, temp->right->harf);
		
		//Adding node to the tree.
		if(isLast==1)
		{
			if(current->next->freq > current->freq) //altı 4'ten büyükse
			{
				//root = Insert(root, temp->right->freq, temp->right->harf);
				root = Insert(root, temp->left->freq, temp->left->harf);
				root = Insert(root, temp->freq, temp->harf);
			}
			else if(current->next->freq < current->freq)
			{
				root = Insert(root, temp->right->freq, temp->right->harf);
				root = Insert(root, temp->freq, temp->harf);
			}
		}
		else
		{
			root = Insert(root, temp->left->freq, temp->left->harf);
			root = Insert(root, temp->right->freq, temp->right->harf);
			root = Insert(root, temp->freq, temp->harf);
		}
		
		//preorder yap root left right
		printf("\n");
		printPreorder(root);
		//inorder yap left root right
		//printInorder(root);
		//postorder yap left, right, root
		//printPostorder(root);
		
		printf("\nAgac olusturuldu.\n");
		
		//Linkli listeden silme işlemi - baştan 2 node silindi
		deleteNode(&head, 0);
		deleteNode(&head, 0);
		
		//Copy linked list
		struct harfSiklik* current2;
		current2=(struct harfSiklik*) malloc(countFarkli*sizeof(struct harfSiklik));

		current=head;
		current2=head;
		while(current!=NULL)
		{
			current2->harf=current->harf;
			current2->freq=current->freq;
			current=current->next;
			//printf("\n current2 harf: %c", current2->harf);
			//printf("\n current2 freq: %d", current2->freq);
			current2=current2->next;
		}
		
		//Push işlemi
		current=head;
		current2=head;
		while(current2->next!=NULL)
		{
			if(current->freq <= temp->freq && (current->next->freq <= temp->freq))
			{
				current=current->next;
			}
			current2=current2->next;
		}
		after(current, temp);
		//push(&(current->next), temp->freq, '\0');
				
		//Printing the linked-list.
		printf("\nPrinting the linked-list.");
		current=head;
		while(current!=NULL)
		{
			printf("\n%d%c", current->freq, current->harf);
			current=current->next;
		}
		//printPreorder(root);
		current=head;
		current=current->next;
		printf("\n------------------\n");
	}
}

/*
	Print fonksiyonları.
	Pre-order kullanıldı ama diğer fonksiyonlar da tanımlandı.
*/
void printPostorder(struct MinHeapNode* node) 
{ 
     if (node == NULL) 
        return; 
  
    printPostorder(node->left); 
    printPostorder(node->right);
	printf(" %d %c", node->freq, node->harf);  
} 

void printInorder(struct MinHeapNode* node) 
{ 
     if (node == NULL) 
          return; 
  
    printInorder(node->left);
	printf(" %d %c", node->freq, node->harf);    
    printInorder(node->right); 
} 

void printPreorder(struct MinHeapNode* node) 
{ 
    if (node == NULL) 
        return; 
    printf("%d %c ", node->freq, node->harf);
    printPreorder(node->left);   
    printPreorder(node->right); 
}     

//Yeni bir node oluşturma.
struct MinHeapNode* GetNewNode(int freq, char harf)
{
	struct MinHeapNode* newNode;
	newNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	
	newNode->freq = freq;
	newNode->harf = harf;
	newNode->left = newNode->right = NULL;
	
	printf("\n%d %c", newNode->freq, newNode->harf);
	
	return newNode;
}

//Min Heap Tree'de arama işlemi
bool Search(struct MinHeapNode* root, int freq, char harf)
{
	if(root==NULL) return false;
	else if(root->freq == freq) return true;
	else if(freq <= root->freq) return Search(root->left, freq, harf);
	else return Search(root->right, freq, harf);
}

//Min Heap Tree'ye insert işlemi uygulanır.
struct MinHeapNode* Insert(struct MinHeapNode* root, int freq, char harf)
{
	if(root == NULL)
	{
		root = GetNewNode(freq, harf);
	}
	else if(freq <= root->freq)
	{
		root->left = Insert(root->left, freq, harf);
	}
	else if(freq > root->freq)
	{
		root->right = Insert(root->right, freq, harf);
	}
	return root;
}

//Linkli listeye ekleme işlemi yapılıyor. 'Push' fonksiyonu ile benzer işleve sahip.
void after(struct harfSiklik *a, struct MinHeapNode *temp)
{
    struct harfSiklik *p;
    p = malloc (sizeof(struct harfSiklik));
    
	p->freq = temp->freq;
	p->harf = temp->harf;
		
    p->next = a->next;
    a->next = p;
}

//Linkli listeden node silme işlemi uygulanır.
void deleteNode(struct harfSiklik **head_ref, int position) 
{ 
   // Eğer boşsa null dönsün.
   if (*head_ref == NULL) 
      return; 
  
   // harfSiklik head = null yaptık. 
   struct harfSiklik* temp = *head_ref; 
  
    // Eğer head'in kaldırılması gerekiyorsa
    if (position == 0) 
    { 
        *head_ref = temp->next;   // head'i değiştir. 
        free(temp);               // eski head'i free et.
        return; 
    } 
  
    // Silinecek olan değeri bul.
    for (int i=0; temp!=NULL && i<position-1; i++) 
         temp = temp->next; 
  
    // Eğer pozisyon node'lardan fazlaysa 
    if (temp == NULL || temp->next == NULL) 
         return; 
  
    // Node temp->next is the harfSiklik to be deleted 
    // Store pointer to the next of harfSiklik to be deleted 
    struct harfSiklik *next = temp->next->next; 
  
    // Linkli listeden free et.
    free(temp->next);  // Free memory 
  
    temp->next = next;
} 

//Insertion Sort fonksiyonu
void insertionSort(struct harfSiklik **head_ref) 
{ 
    // Initialization.
    struct harfSiklik *sorted = NULL; 
  
    // Gezinti yapılır.
    struct harfSiklik *current = *head_ref; 
    while (current != NULL) 
    { 
        // Diğer iterasyon için sakla.
        struct harfSiklik *next = current->next; 
        // Şu anki değeri, düzenlenmiş linked-list'e insert et.
        sortedInsert(&sorted, current); 
        // Şimdikini güncelle. 
        current = next; 
    } 
  
    // Update işlemi.
    *head_ref = sorted; 
} 

void sortedInsert(struct harfSiklik** head_ref, struct harfSiklik* new_harfSiklik) 
{ 
    struct harfSiklik* current; 
	
    if (*head_ref == NULL || (*head_ref)->freq >= new_harfSiklik->freq) 
    { 
        new_harfSiklik->next = *head_ref; 
        *head_ref = new_harfSiklik; 
    } 
    else
    { 
        current = *head_ref; 
        while (current->next!=NULL && 
               current->next->freq < new_harfSiklik->freq) 
        { 
            current = current->next; 
        } 
        new_harfSiklik->next = current->next; 
        current->next = new_harfSiklik; 
    } 
}

//Linkli listeye push etme işlemi.
void push(struct harfSiklik** head_ref, int freq, char harf) 
{ 
    // Allocate işlemi
    struct harfSiklik* new_harfSiklik = 
            (struct harfSiklik*) malloc(sizeof(struct harfSiklik)); 
  
    new_harfSiklik->freq=freq; 
	new_harfSiklik->harf=harf;
  
    new_harfSiklik->next = (*head_ref); 
  
    // head'i ata.
    (*head_ref) = new_harfSiklik; 
} 