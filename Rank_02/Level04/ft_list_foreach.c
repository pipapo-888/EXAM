
typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

void ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list *now;

	now = begin_list;
	while (now)
	{
		f(now -> data);
		now = now -> next;
	}
	return ;
}



#include <stdio.h>
#include <stdlib.h>

// 出力用関数（関数ポインタで渡す）
void print_str(void *data)
{
    printf("%s\n", (char *)data);
}

int main(void)
{
    // ノードを3つ作成
    t_list *n1 = malloc(sizeof(t_list));
    t_list *n2 = malloc(sizeof(t_list));
    t_list *n3 = malloc(sizeof(t_list));

    // データを代入
    n1->data = "hello";
    n2->data = "world";
    n3->data = "!";

    // リンクする
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;

    // テスト実行
    ft_list_foreach(n1, print_str);

    // メモリ解放（テストでは省略してもOK）
    free(n1);
    free(n2);
    free(n3);

    return 0;
}
