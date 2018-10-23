#ifdef __linux__
   #define CLR_SCRN "clear"
#else
   #error "NOT SUPPORTED ARCHITECTURE"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void MANFunc();                 //прототипы функций.
extern void CRTFunc(register char * );
extern int OPFFunc(register char * );
extern int RMVFunc(register char * );

int main(void)
{

    char * buffer = (char * ) malloc(200* sizeof(char)); //буффер ввода

    if (!buffer) // Проверка выделения памяти в heap.
    {
        fprintf(stdout,"Ошибка выделения динамической памяти.\n");
        return EXIT_FAILURE;
    }
    system(CLR_SCRN);   //очистка экрана
    fprintf(stdout,"Интерпретатор командной строки. Для получения"
    " справочной информации, пожалуйста, введите команду man."
    "\nМай 2016.\n");
    while (1)   //цикл анализа входных даных.
    {
        fprintf(stdout,"Ввод команды: ");
        fgets(buffer,200,stdin);
        if (strcmp(buffer,"man\n")==0) MANFunc();
        else if (strcmp(buffer,"clr\n")==0) system(CLR_SCRN); 
        else if (strncmp(buffer,"crt ",4)==0) CRTFunc(buffer);
        else if (strncmp(buffer,"opf ",4)==0) OPFFunc(buffer);
        else if (strncmp(buffer,"rmv ",4)==0) RMVFunc(buffer);
        else if (strcmp(buffer,"qt\n")==0) break;
        else if (strcmp(buffer,"\n")!=0 && buffer[0]!= ' ') 
           fprintf(stdout,"%s Строка не принадлежит глубине "
        "вхождений команд на внутреннем уровне интерпретатора." 
        "Для информации обратитесь к справочной поддержке.\n",
        buffer);
    }
    free(buffer);
    buffer=NULL;
    return EXIT_SUCCESS;  
}

void MANFunc()
{
    fprintf(stdout,"\nНебольшой guide по быстрому и эффективному "      
    "использованию сего продукта.\n\nКоманды:\ncrt\t - \tСоздание "    
    "файла (возможно создание нескольких файлов одновременно).\n"
    "opf\t - \tОткрытие файла\nrmv\t - \tУдаления файла(возможно "    
    "удаление несколько файлов одновременно).\nqt\t - \tЗавершение " 
    "работы интерпретатора.\nclr\t - \tОчистка рабочего экрана.\n");     
}

void CRTFunc(register char *str)
{
    
    FILE * sv;
    char * token=strtok(str," \n");
   
    while (token != NULL) //пока есть лексемы
    {
        if (strcmp(token,"crt")!=0)
        {
            sv=fopen(token,"w"); //создание файла, 
            fclose(sv);          //или перезапись существующего.
        }
        token = strtok (NULL, " \n");
    }
}

int OPFFunc (register char * str)
{
      
    FILE * sv;
    char * token=strtok(str," ");
    char c;

    token = strtok (NULL, " \n");
    if ((sv=fopen(token,"r+"))==NULL)
    {
        perror("Невозможно открыть файл:");
        return EXIT_FAILURE;
    }
    else
    {
        system(CLR_SCRN);  //чтение из файла
        while ((c=getc(sv)) != EOF )
           putchar(c);
        while ( ( c=getc(stdin) ) != '\n')
           putc(c,sv);    // и запись
        fclose(sv);   
    }
    return EXIT_SUCCESS;    
}

int RMVFunc(register char *str)
{
    
    char * token=strtok(str," \n");
   
    token = strtok (NULL, " \n");
    while (token != NULL) 
    {
        if (remove(token) != 0 ) 
        {
            perror("Невозможно уничтожить файл: ");
            return EXIT_FAILURE;
        }
        token = strtok (NULL, " \n");
    }
    return EXIT_SUCCESS;
}
