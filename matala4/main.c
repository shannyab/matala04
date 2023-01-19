#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
typedef struct GRAPH_NODE_ *pnode;;
typedef struct edge_{
int weight;
pnode endpoint;
struct edge_ *next;
}edge,*pedge;
typedef struct queueNode{
pnode nodedata;
int priority;
struct queueNode* next;
}queuenode;
typedef struct GRAPH_NODE_{
int node_num;
pedge edges;
struct GRAPH_NODE_ *next;
int seq;
}node,*pnode;
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
void dijkstra(int *arr,pnode here);
void permotation(int* cities,int start,int end,int size_of_nodes,int* ans,pnode head);
void sweap(int* a,int* b);
pnode generate(int k);
pnode newnode(int k,pnode next);
pnode find_node(int data,pnode head);
void remove_out_edges(pnode here);
void remove_edge_to(int data,pnode here);
pnode insert_node(int data,pnode *head);
queuenode* newqueueNode(pnode data,int p);
pnode pop(queuenode** head);
void push(queuenode** head,pnode d,int p);
int isEmpty(queuenode** head);
pedge nwedge(int weight,pedge next,pnode dest);
pedge nwedge(int weight,pedge next,pnode dest){
pedge p=(pedge) malloc(sizeof(edge));
p->endpoint=dest;
p->next=next;
p->weight=weight;
return p;
}
pnode newnode(int k,pnode next){
pnode p=(pnode) malloc(sizeof(node));
p->node_num=k;
p->next=next;
p->edges=NULL;
return p;
}
pnode find_node(int data,pnode head){
while (head){
if (head->node_num == data){
return head;
}
head=head->next;
}
return NULL;
}
pnode generate(int k){
pnode head=NULL;
for (int i=k-1;i>=0;i--){
head=newnode(i,head);
}
return head;
}
void remove_out_edges(pnode here){
pedge next=here->edges;
while(next){
pedge prev=next;
next=next->next;
free(prev);
}
}
void remove_edge_to(int data,pnode here){
pedge check_edge=here->edges;
if(check_edge){
if (check_edge->endpoint->node_num == data){
pedge delete=check_edge;
here->edges=check_edge->next;
free(delete);
return;
}
while(check_edge->next != NULL){
if (check_edge->next->endpoint->node_num == data){
pedge delete=check_edge->next;
check_edge->next=delete->next;
free(delete);
return;
}
check_edge=check_edge->next;
}
}
}
pnode insert_node(int data,pnode *head){
pnode *p=head;
while ((*p)->next)
   {
if((*p)->node_num< data && (*p)->next->node_num> data){
pnode new=newnode(data,(*p)->next);
(*p)->next=new;
return new;
}
p=&((*p)->next);
}
pnode new=newnode(data,(*p)->next);
(*p)->next=new;
return new;
}
void build_graph_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode here=find_node(i,*head);
pedge prev=NULL;
while(scanf("%d",&i)==1){
pnode dest=find_node(i,*head);
scanf("%d",&i);
prev=nwedge(i,prev,dest);
}
here->edges=prev;
}
void insert_node_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode here=find_node(i,*head);
if (*head == NULL){
*head=newnode(i,NULL);
here=*head;
}
else if(here != NULL){
remove_out_edges(here);
}
else{
here=insert_node(i,head);
}
pedge prev=NULL;
while(scanf("%d",&i)==1){
pnode dest=find_node(i,*head);
scanf("%d",&i);
prev=nwedge(i,prev,dest);
}
here->edges=prev;
}
void delete_node_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode check_node=*head;
pnode delete=NULL;
if (check_node->node_num == i){
*head=check_node->next;
delete=check_node;
}
else{
while(check_node->next){
if (check_node->next->node_num == i){
delete=check_node->next;
check_node->next=delete->next;
break;
}
check_node= check_node->next;
}
}
check_node=*head;
while(check_node){
remove_edge_to(i,check_node);
check_node=check_node->next;
}
remove_out_edges(delete);
free(delete);
}
queuenode* newqueueNode(pnode data,int p){
	queuenode* temp=(queuenode*)malloc(sizeof(queuenode));
	temp->nodedata=data;
	temp->priority=p;
	temp->next=NULL;
	return temp;
}
pnode pop(queuenode** head){
	pnode temp=(*head)->nodedata;
	queuenode* temptofree=*head;
	(*head)=(*head)->next;
	free(temptofree);
	return temp;
}
void push(queuenode** head,pnode d,int p){
	queuenode* start=(*head);
	queuenode* temp=newqueueNode(d,p);
	if (isEmpty(head)){
		(*head)=temp;
		return;
	}
	
	if ((*head)->priority > p){
		temp->next=*head;
		(*head)=temp;
	}
	else{

		while (start->next != NULL &&
			start->next->priority < p){
			start=start->next;
		}

		temp->next=start->next;
		start->next=temp;
	}
}
int isEmpty(queuenode** head){
	return (*head) == NULL;
}
void printGraph_cmd(pnode head){  //for self debug
while(head){
printf("node id: %d\n",head->node_num);
pedge here=head->edges;
while(here){
printf("%d -> %d   w: %d\n",head->node_num,here->endpoint->node_num,here->weight);
here= here->next;
}
head=head->next;
}
}
void deleteGraph_cmd(pnode* head){
pnode here=*head;
while(here){
remove_out_edges(here);
pnode delete=here;
here=here->next;
free(delete);
}
}
void shortsPath_cmd(pnode head){
int src;
int dest;
while(scanf("%d",&src)==0);
while(scanf("%d",&dest)==0);
//int max=0;
pnode here;
pnode curr=head;
int j=0;
int idxdest;
int idxsrc;
while (curr){
curr->seq=j;
if (curr->node_num == src){
here=curr;
idxsrc=j;
}
if (curr->node_num == dest){
idxdest=j;
}
j++;
curr= curr->next;
}
int *arr=(int*)malloc(sizeof(int)*j);
for (int i=0;i<j;i++){
arr[i]=INT_MAX;
}
arr[idxsrc]=0;
dijkstra(arr,here);
if (arr[idxdest]<INT_MAX){
printf("Dijsktra shortest path: %d \n",arr[idxdest]);
}
else{
printf("Dijsktra shortest path: -1 \n");
}
free(arr);
}
void dijkstra(int *arr,pnode here){
queuenode* here_queue=newqueueNode(here,0);
while (!isEmpty(&here_queue)){
here=pop(&here_queue);
pedge curr_edge=here->edges;
while(curr_edge){
if (arr[here->seq] + curr_edge->weight < arr[curr_edge->endpoint->seq]){
arr[curr_edge->endpoint->seq]=arr[here->seq] + curr_edge->weight;
push(&here_queue,curr_edge->endpoint,arr[curr_edge->endpoint->seq]);
}
curr_edge= curr_edge->next;
}
}
}
void TSP_cmd(pnode head){
int j;
scanf("%d",&j);
int *cities=(int*)malloc(sizeof(int)*j);
for(int i=0; i<j; i++){
scanf("%d",&cities[i]);
}
int max=0;
pnode here=head;
while (here){
here->seq=max;
max++;
here= here->next;
}
int ans=INT_MAX;
permotation(cities,0,j-1,max,&ans,head);
if (ans != INT_MAX){
printf("TSP shortest path: %d \n",ans);
}
else{
printf("TSP shortest path: -1 \n");
}
free(cities);
}
void permotation(int* cities,int start,int end,int size_of_nodes,int* ans,pnode head){
if (start == end){
int check =0;
int *dxtra=(int*)malloc(sizeof(int)*size_of_nodes);
for (int i=0;i<size_of_nodes;i++){
dxtra[i]= INT_MAX;
}
pnode here=find_node(cities[0],head);
dxtra[here->seq]=0;
for (int i=1;i<=end;i++){
dijkstra(dxtra,here);
if (dxtra[find_node(cities[i],head)->seq] == INT_MAX){
free (dxtra);
return;
}
here=find_node(cities[i],head);
check=check + dxtra[here->seq];
for (int j=0;j<size_of_nodes;j++){
dxtra[j]= INT_MAX;
}
dxtra[here->seq]=0;  
}
free (dxtra);
if (check < *ans && check !=0){
*ans=check;
}
return;
}
for (int k=start;k<=end;k++){
sweap(cities+k,cities+start);
permotation(cities,start+1,end,size_of_nodes,ans,head);
sweap(cities+k,cities+start);
}
}
void sweap(int* a,int* b){
int temp=*a;
*a=*b;
*b=temp;
}
int main(){
char s;
int k;
pnode head=NULL;
int end_of_file=0;
while(end_of_file!=EOF){
end_of_file=scanf("%c",&s);
if (s == 'A'){
deleteGraph_cmd(&head);
scanf("%d",&k);
head=generate(k);
}
if (s == 'n'){
build_graph_cmd(&head);
}
if (s == 'B'){
insert_node_cmd(&head);
}
if (s=='p'){
printGraph_cmd(head);
}
if (s=='S'){
shortsPath_cmd(head);
}
if (s=='D'){
delete_node_cmd(&head);
}
if (s=='T'){
TSP_cmd(head);
}
}
deleteGraph_cmd(&head);
return 0;
}