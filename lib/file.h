#ifndef FILE_H_
#define FILE_H_

#ifndef FILE_CONTENT_READ
#define FILE_CONTENT_READ 0
#endif /* FILE_CONTENT_READ */

#ifndef FILE_CONTENT_UNREAD
#define FILE_CONTENT_UNREAD -1
#endif /* FILE_CONTENT_UNREAD */

#ifndef CANNOT_OPEN_FILE
#define CANNOT_OPEN_FILE -2
#endif /* CANNOT_OPEN_FILE */

int get_file_content(char const *filename, char **buffer);

#endif /* FILE_H_ */
