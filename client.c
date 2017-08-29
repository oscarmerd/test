#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <json/json.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
char* str;
int fd = 0;
struct sockaddr_in demoserverAddr;

fd = socket(AF_INET, SOCK_STREAM, 0);

if (fd < 0)
{
    printf("Error : Could not create socket\n");
    return 1;
}
else
{
    demoserverAddr.sin_family = AF_INET;
    demoserverAddr.sin_port = htons(8888);
    demoserverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(demoserverAddr.sin_zero, '\0', sizeof(demoserverAddr.sin_zero));
}

if (connect(fd, (const struct sockaddr *)&demoserverAddr, sizeof(demoserverAddr)) < 0)
{
     printf("ERROR connecting to server\n");
     return 1;
}


json_object *jobj = json_object_new_object();


json_object *jstring = json_object_new_string("Whats my best Song");


json_object *jint = json_object_new_int(10);


json_object *jboolean = json_object_new_boolean(1);


json_object *jdouble = json_object_new_double(2.14);


json_object *jarray = json_object_new_array();


json_object *jstring1 = json_object_new_string("tecno");
json_object *jstring2 = json_object_new_string("electron");
json_object *jstring3 = json_object_new_string("hiphop");


json_object_array_add(jarray,jstring1);
json_object_array_add(jarray,jstring2);
json_object_array_add(jarray,jstring3);


json_object_object_add(jobj,"Whats the name", jstring);
json_object_object_add(jobj,"Expedition", jboolean);
json_object_object_add(jobj,"Listening percentage", jdouble);
json_object_object_add(jobj,"Music number", jint);
json_object_object_add(jobj,"Music category", jarray);

printf("Size of JSON object- %lu\n", sizeof(jobj));
printf("Size of JSON_TO_STRING- %lu,\n %s\n", sizeof(json_object_to_json_string(jobj)), json_object_to_json_string(jobj));

    char temp_buff[1024];

    if (strcpy(temp_buff, json_object_to_json_string(jobj)) == NULL)
    {
        perror("strcpy");
        return EXIT_FAILURE;
    }

    if (write(fd, temp_buff, strlen(temp_buff)) == -1)
    {
        perror("write");
        return EXIT_FAILURE;
    }

    printf("Written data\n");
    return EXIT_SUCCESS;
}