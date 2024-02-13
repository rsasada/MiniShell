/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:02:27 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/12 17:02:27 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void append_arg(t_ast_node *args_node, t_ast_node *arg_node);

static int is_valid_arg(char *arg) {
    char *a;

    a = arg;
    while (a && *a != '\0') {
        if (!ft_isalnum(*a) && *a != '_')
            return (0);
        a++;
    }
    return (1);
}

void ft_unset(t_app *app, t_list *argv, pid_t *pid) {
    pid_t *first_pid;
    t_list *argv_cur;
    char *arg;

    if (!app || !app->pid_storage || !argv || !pid)
        return;
    first_pid = (pid_t *) (app->pid_storage->content);
    if (pid != first_pid)
        return;
    argv_cur = argv;
    while (argv_cur) {
        arg = ((t_ast_node *) (argv_cur->content))->u_node_data.file_name_val;
        if (!is_valid_arg(arg)) {
            ft_putstr_fd("push: unset: `", STDERR_FILENO);
            ft_putstr_fd(arg, STDERR_FILENO);
            handling_error("': not a valid identifier", 1);
        }
        remove_env(&(app->env_lst), arg);
        argv_cur = argv_cur->next;
    }
}

void add_env(t_list **lst, char *key, char *value) {
    t_env *env = malloc(sizeof(t_env));
    if (!env)
        return;
    env->key = ft_strdup(key); // strdup 함수는 문자열을 동적으로 복사합니다.
    env->value = ft_strdup(value);
    ft_lstadd_back(lst, ft_lstnew(env));
}

void print_env_list(t_list *lst) {
    t_list *current = lst;
    t_env *env;
    while (current) {
        env = (t_env *) current->content;
        printf("%s=%s\n", env->key, env->value);
        current = current->next;
    }
}

t_list *create_arg_list(char **args) {
    t_list *head = NULL;
    t_list **current = &head;
    while (*args) {
        *current = ft_lstnew(*args);
        current = &(*current)->next;
        args++;
    }
    return head;
}
// main 함수


t_ast_node *create_argv_from_array(char *args[]) {
    t_ast_node *args_node = create_arg_list_node();
    int i = 0;
    while (args[i] != NULL) {
        t_ast_node *arg_node = create_file_name_node(args[i]);
        append_arg(args_node, arg_node);
        i++;
    }
    return args_node;
}


t_env *create_env_var(const char *key, const char *value) {
    t_env *env_var = malloc(sizeof(t_env));
    if (!env_var) return NULL;

    env_var->key = ft_strdup(key); // key 문자열을 동적으로 복사
    if (!env_var->key) {
        free(env_var);
        return NULL;
    }

    env_var->value = ft_strdup(value); // value 문자열을 동적으로 복사
    if (!env_var->value) {
        free(env_var->key);
        free(env_var);
        return NULL;
    }

    return env_var;
}

void add_env_var_to_list(t_list **env_list, const char *key, const char *value) {
    t_env *new_env_var = create_env_var(key, value);
    if (!new_env_var) {
        // 메모리 할당 실패 처리
        return;
    }
    ft_lstadd_back(env_list, ft_lstnew(new_env_var));
}


int main(void) {
    t_app app;
    pid_t dummy_pid = 123; // ft_unset 함수에서 사용되는 pid, 예제를 위한 임시 값

    // 앱 초기화
    app.env_lst = NULL;
    app.pid_storage = malloc(sizeof(t_list));
    app.pid_storage->content = &dummy_pid;
    app.pid_storage->next = NULL;

    // 환경변수 추가
    add_env_var_to_list(&app.env_lst, "PATH", "/usr/bin");
    add_env_var_to_list(&app.env_lst, "HOME", "/home/user");
    add_env_var_to_list(&app.env_lst, "LANG", "en_US.UTF-8");    // 삭제 전 프린트

    printf("Before unset:\n");
    print_env_list(app.env_lst);

    // 더미 데이터 생성을 위한 인자 리스트 생성
    char *args_to_unset[] = {"arg12+", "HOME", NULL}; // 삭제될 환경 변수 이름
    t_ast_node *args_node = create_argv_from_array(args_to_unset); // 이 함수는 문자열 배열을 기반으로 인자 리스트를 생성합니다.

    // `ft_unset`을 위한 `t_list` 생성 및 실행
    // 주의: 여기서 args_node의 arg_list를 직접 전달
    ft_unset(&app, args_node->u_node_data.arg_list, &dummy_pid);


    // 삭제 후 프린트
    printf("After unset:\n");
    print_env_list(app.env_lst);

    return 0;
}