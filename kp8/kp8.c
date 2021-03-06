#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
char data[20];
struct item* prev;
struct item* next;
}item;

typedef struct{
item* node;
} iterator;

iterator next(iterator* i){
i->node = i->node->next;
return *i;
}

iterator prev(iterator* i){
i->node = i->node->prev;
return *i;
}

char* fetch(const iterator* i){
return i->node->data;
}

int equal(const iterator* lhs, const iterator* rhs){
return lhs->node == rhs->node;
}

typedef struct{
item* head;
int size;
}list;

void create(list* l){
l->head = 0;
l->size = 0;
}

iterator search(const list* l, const int* num){
int j = 1;
iterator i;
i.node = l->head;
while (j < *num){
next(&i);
j++;
}
return i;
}

iterator get_last(list* l){
iterator i;
i.node = l->head;
while (i.node->next){
i = next(&i);
}
return i;
}

void print_list(const list *l){
int k = 0;
if (l->head == 0){
printf("Список пустой\n");
return;
}
iterator i;
i.node = l->head;
while(i.node->next){
k++;
printf("%d | %s\n", k, fetch(&i));
i = next(&i);
}
k++;
printf("%d | %s\n", k, fetch(&i));
}

void insert(list* l, iterator* i, const char t[20]){
iterator res;
res.node = (item*) malloc(sizeof(item));
iterator h;
h.node = l->head;
if (l->head == 0){
printf("Список пуст\nДобавляемый элемент будет первым\n");
l->head = (item*) malloc(sizeof(item));
strcpy(l->head->data, t);
l->head->next = 0;
l->head->prev = 0;
l->size++;
return;
}
if (equal(i, &h)){
strcpy(res.node->data, t);
res.node->next = l->head;
res.node->prev = 0;
l->head->prev = res.node;
l->head = res.node;
l->size++;
return;
}
strcpy(res.node->data, t);
res.node->next = i->node;
res.node->prev = i->node->prev;
res.node->prev->next = res.node;
i->node->prev = res.node;
l->size++;
return;
}

void _delete(list *l, iterator* i){
iterator h;
h.node = l->head;
if (l->head == 0){
printf("Список пустой\n");
return;
}
if (equal(i, &h)){
item* i;
i = l->head->next;
l->head->next = 0;
free(l->head);
l->head = i;
l->size--;
return;
}
if (i->node->next == 0){
i->node->prev->next = i->node->next;
l->size--;
free(i->node);
i->node = 0;
return;
}
i->node->prev->next= i->node->next;
i->node->next->prev = i->node->prev;
i->node->next = i->node->prev = 0;
l->size--;
free(i->node);
i->node = 0;
}

int size(const list* l){
return l->size;
}

void add(list *l, int* k){
iterator last = get_last(l);
iterator h;
h.node = l->head;
while (*k > 0){
insert(l, &h, last.node->data);
(*k)--;
}
}

void reverse(const list *l){
	int count = size(l);
	iterator *k, *j;
	char tmp1[20];
	char tmp2[20];

	for (int i = 0; i <= count / 2; ++i)
	{
		k = search(&l, &i);
		j = search(&l, count-i)
		tmp1 = k->node;
		tmp2 = j->node;
		k->node = tmp2;
		j->node = tmp1;
	}
	

}





int main(){
	int chose, num;
	int len;
	int g = 1;
	list l;
	create(&l);
	iterator i, j;
	char t[20];
	while(g == 1){
		printf("Меню:\n\nВыберите действие:\n1)Создать список\n2)Печать списка\n3)Вставка нового элемента в список\n4)Удалить эелемент в списке\n5)Вывод длины списка\n6)Перевернуть список\n7)Выход\n");
		scanf("%d", &chose);
		switch(chose){
			case 1:
				break;
			case 2:
				print_list(&l);
				break;
			case 3:
				printf("Введите элемент, который нужно вставить\n");
				scanf("%s", t);
				insert(&l, &i, t);
				i = get_last(&l);
				break;
			case 4:
				printf("Введите элемент, который нужно удалить\n");
				scanf("%d", &num);
				j = search(&l, &num);
				delete(&l, &j);
				break;
			case 5:
				len = size(l);
				printf("%d\n", &len);
				break;
			case 6:
				g = 0;
				break;
		}
	}
	return 0;
}