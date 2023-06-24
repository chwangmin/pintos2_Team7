#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

bool lazy_load_segment(struct page *page, void *aux);
tid_t process_create_initd (const char *file_name);
tid_t process_fork (const char *name, struct intr_frame *if_);
int process_exec (void *f_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (struct thread *next);
/* project 2 */
void argument_stack(char **argv, int argc, void **rsp);
struct thread *get_child_process(int pid);
int process_add_file(struct file *f);
struct file *process_get_file(int fd);
void process_close_file(int fd);
struct thread *get_child_process(int pid);
struct lazy_load_arg		// lazy_load 구조체 설정.
{
	struct file *file;		// 파일 객체 저장할 구조체
	off_t ofs;				// 이 페이지에서 읽기 시작할 위치
	uint32_t read_bytes;	// 이 페이지에서 읽어야 하는 바이트 수
	uint32_t zero_bytes;	// 이 페이지에서 read_bytes만큼 읽고 공간이 남아 0으로 채워야 하는 바이트 수
};
#endif /* userprog/process.h */
