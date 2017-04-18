#define _CRT_SECURE_NO_WARNINGS
#define MAX 1024*1024*5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int loading_res(struct dict **p, const char *filename);
int search_word(const struct dict *p, const char* key, char *content, int size);
void on_close(const struct dict *p, int size);
void strutil(char ** str);
struct dict {
	char *key;
	char *content;
	struct dict *next;
};
void main(int count ,char *a[])
{
	
	if (count < 2) {
		printf("参数不足，程序退出");
		return;
	}
	int size = 0;
	struct dict *p = NULL;
	long start_time = clock();
	size = loading_res(&p , a[1]);
	long end_time = clock();
	if (size == 0)
	{
		printf("资源为空\n");
		return;
	}
	printf("加载资源 耗时：%d ms\n",(end_time - start_time));
	char key[1024] = { 0 };
	char content[1024] = { 0 };
	while (1) 
	{
		memset(key,0,1024);
		memset(content, 0, 1024);
		scanf("%s", key);
		if (strncmp(key, "exit", 4) == 0) {
			break;
		}
		start_time = clock();
		int code = search_word(p, key, content, size);
		end_time = clock();
		printf("查询 耗时：%d ms\n", (end_time - start_time));
		
		if (code == 1) {
		    //strutil(&content);
			printf("查询结果：%s", content);
		
		}
		else  printf("not found ");
		printf("\n");
	}
	start_time = clock();
	on_close(p,size);
	end_time = clock();
	printf("释放资源 耗时：%d ms\n", (end_time - start_time));

	return;
}
void on_close(const struct dict *p, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if(p[i].content)
		    free(p[i].content);
		if(p[i].key)
     		free(p[i].key);
	}
	free(p);
	return;

}
int search_word(const struct dict *p, const char* key, char *content,int size)
{
	
	for (int i = 0; i < size; i++)
	{
		if (p[i].key == NULL || p[i].content == NULL)
			continue;
		if (strncmp(p[i].key,key,strlen(key)) == 0) 
		{
			strcpy(content,p[i].content);
			//printf("key = %s  key = %s\n",key ,p[i].key );
			//printf("content = %s  content = %s\n", content, p[i].content);
			return 1;
		}
	}
	return 0;

}
int loading_res(const struct dict **p, const char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		return 0;
	}
	int i = 0;
	*p = calloc(MAX, sizeof(struct dict));
	struct dict *p1 = *p;
	char buf[1024] = { 0 };
	int len = 0;
	while (!feof(f))
	{
		memset(buf, 0, sizeof(buf));
		fscanf(f, "%s", buf);
		len = strlen(buf);
		if (len > 0)
		{

			p1[i].key = (char*)calloc(sizeof(buf),len + 1);
			strcpy(p1[i].key,buf);
			memset(buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), f);
			p1[i].content = (char*)calloc(sizeof(buf), len + 1);
			strcpy(p1[i].content, buf);
			i++;
		}
		
	}
	fclose(f);
	return i;
}
void strutil(char **str)
{
	//printf("n = %d   \n\\ =   %d\n32 = %d\n", 'n', '\\', ' ');
	int len = strlen(*str);
	if (strncmp("\\n", *str, 2) == 0)
	{
		*str = (*str) + 2;
	}
	for (int i = 0; i < len -1; i++)
	{
		
		if (strncmp(" ", *str, 1) == 0)
		{
			printf("str = %s\n",*str);
			(*str)++;
		}
		else return;
	}
}