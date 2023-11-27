/***********************************************
*
* @Proposito:  The market
* @Autor/es: Daniela Amato Arrieta
* @Fecha creacion: 28/03/2022
* @Fecha ultima modificacion: 07/03/2022
*
************************************************/

 #include <stdio.h>
  2 #include <string.h>
  3
  4 #define MAX 30                                                                                                     //constantes
  5 #define MAX2 70
  6
  7 typedef struct {                                                                                                   //tipo propio de Producto
  8     char nombre[MAX2];
  9     int stock;
 10     float precio;
 11 }Producto;
 12
 
 /***********************************************
*
* @Finalidad: desplegar menu de opciones
* @Parametros: in/out: opcion (opcion escogida del menu)
* @Retorno: opcion escogida
*
************************************************/
 
 13 int showMenu (int opcion) {
 14
 15     do {                                                                                                            //bucle que repite el menu
 16         printf ("\n1. Load products from supplier | 2. List products | 3. Show product | 4. Exit\n");
 17         printf ("Select option: ");
 18         scanf ("%d", &opcion);
 19
 20         if (opcion < 1 || opcion > 4) {                                                                             //condicional que verifica opcion
 21             printf ("\nERROR: Wrong option number\n\n");
 22         }
 23     } while (opcion < 1 || opcion > 4);
 24
 25     return opcion;
 26 }
 27
 /***********************************************
*
* @Finalidad: verificar repeticion de productos
* @Parametros: in: numprod (numero de productos)
*              in: aux (nuevo producto)
*              in : a1 (listado de productos)
* @Retorno: flag (valor actualizado)
*
************************************************/
 28 int checkGood (int numprod, Producto aux, Producto a1[MAX]) {
 29     int i, flag = 0;                                                                                                //contadores y flag
 30
 31     for (i = 0; i < numprod; i++) {                                                                                 //bucle que recorre los productos
 32         if (strcmp (a1[i].nombre, aux.nombre) == 0) {                                                               //condicional que compara productos
 33             a1[i].stock = a1[i].stock + aux.stock;
 34             if (aux.precio > a1[i].precio) {                                                                        //condicional que compara precios
 35                 a1[i].precio = aux.precio;
 36             }
 37             flag = 1;
 38         }
 39     }
 40
 41     return flag;
 42 }
 43
/***********************************************
*
* @Finalidad: cargar fichero 1
* @Parametros: in: fichero
*              in: a1 (listado de productos)
*              in/out: numprod (numero de productos) 
* @Retorno: numprod (numero de productos)
*
************************************************/
 44 int loadFile1 (FILE *f, Producto a1[MAX], int numprod) {
 45     int i, flag = 0, flag2 = 0;                                                                                     //contadores y flags
 46     char kk;                                                                                                        //variable basura
 47     Producto aux;                                                                                                   //variable auxiliar
 48
 50         fscanf (f, "%d", &aux.stock);
 51         while (!feof (f)) {                                                                                         //bucle que recorre todo el fichero
 52             fscanf (f, "%c", &kk);
 53             fscanf (f, "%f", &aux.precio);
 54             fscanf (f, "%c", &kk);
 55             fgets (aux.nombre, MAX, f);
 56             aux.nombre[strlen (aux.nombre) - 1] = '\0';
 57
 58             for (i = 0; i < strlen (aux.nombre); i++) {                                                             //bucle que recorre el nombre del producto
 59                 if (aux.nombre[i] == '@') {                                                                         //condicional que verifica nombre
 60                     flag = 1;
 61                 }
                    else {
                        flag = 0;
                    }
 62             }
 63
 64             if (flag == 0 && aux.stock != 0) {                                                                      //condiconal que verifica stock
 65                 flag2 = checkGood (numprod, aux, a1);
 66
 67                 if (flag2 == 0) {                                                                                   //condiconal que guarda producto    
 68                     strcpy (a1[numprod].nombre, aux.nombre);
 69                     a1[numprod].stock = aux.stock;
 70                     a1[numprod].precio = aux.precio;
 71                     numprod++;
 72                 }
 73                 flag = 1;
 74                 flag2 = 0;
 75             }
 76
 77             fscanf (f, "%d", &aux.stock);
 78         }
 79
 80         fclose (f);
 81
 82     return numprod;
 83 }
 /***********************************************
*
* @Finalidad: cargar fichero 2
* @Parametros: in: fichero
*              in: a1 (listado de productos)
*              in/out: numprod (numero de productos)
* @Retorno: numprod (numero de productos)
*
************************************************/
 84
 85 int loadFile2 (FILE *g, Producto a1[MAX], int numprod) {
 86     char basura[MAX2], kk;                                                                                          //variables basura
 87     Producto aux;                                                                                                   //variable auxiliar
 88     int flag = 0, i, flag2 = 0;                                                                                     //contadores y flags
 89
 90     fscanf (g, "%s", basura);
 91     while (!feof (g)) {                                                                                             //bucle que recorre todo el fichero
 92         fscanf (g, "%c", &kk);
 93         fscanf (g, "%s", basura);
 94         fscanf (g, "%c", &kk);
 95         fgets (aux.nombre, MAX, g);
 96         aux.nombre[strlen (aux.nombre) - 1] = '\0';
 97         fscanf (g, "%s", basura);
 98         fscanf (g, "%f", &aux.precio);
 99         fscanf (g, "%s", basura);
100         fscanf (g, "%s", basura);
101         fscanf (g, "%d", &aux.stock);
102
103         for (i = 0; i < strlen (aux.nombre); i++) {                                                                 //bucle que recorre nombre del producto
104             if (aux.nombre[i] == '@') {                                                                             //condicional que verifica nombre
105                 flag = 1;
106             }
                else {
                    flag = 0;
                }
107         }
108
109         if (flag == 0 && aux.stock != 0) {                                                                          //condicional que verifica stock
110             flag2 = checkGood (numprod, aux, a1);
111
112             if (flag2 == 0) {                                                                                       //condicional que guarda producto
113                 strcpy (a1[numprod].nombre, aux.nombre);
114                 a1[numprod].stock = aux.stock;
115                 a1[numprod].precio = aux.precio;
116                 numprod++;
117             }
118             flag2 = 0;
119             flag = 0;
120         }
121         fscanf (g, "%s", basura);
122     }
123
124         fclose (g);
125
126     return numprod;
127 }
128
/***********************************************
*
* @Finalidad: cargar fichero 3
* @Parametros: in: fichero
*              in: a1 (listado de productos)
*              in/out: numprod (numero de productos)
* @Retorno: numprod (numero de productos)
*
************************************************/
129 int loadFile3 (FILE *h, Producto a1 [MAX], int numprod){
130     Producto aux;                                                                                                   //variable auxiliar
131     int i, flag = 0, flag2 = 0;                                                                                     //contador y flags
132
133     fread (&aux, sizeof(Producto), 1, h);
134
135     while(!feof(h)) {                                                                                               //bucle que recorre todo el fichero
136
137         for (i = 0; i < strlen (aux.nombre); i++) {                                                                 //bucle que recorre el nombre
138             if (aux.nombre[i] == '@') {                                                                             //condicional que verifica el nombre
139                 flag = 1;
140             }
                else {
                    flag = 0;
                }
141         }
142
143         if (flag == 0 && aux.stock != 0) {                                                                          //condicional que verifica el stock
144             flag2 = checkGood (numprod, aux, a1);
145             if (flag2 == 0) {                                                                                       //condicional que guarda producto
146                 strcpy (a1[numprod].nombre, aux.nombre);
147                 a1[numprod].stock = aux.stock;
148                 a1[numprod].precio = aux.precio;
149                 numprod++;
150             }
151             flag2 = 0;
152             flag = 0;
153         }
154         fread (&aux, sizeof(Producto), 1, h);
155     }
156
157     return numprod;
158 }
/***********************************************
*
* @Finalidad: mostrar listado de productos
* @Parametros: in: a1 (listado de productos)
*              in/out: numprod (numero de productos)
* @Retorno: numprod (numero de productos)
*
************************************************/
160 void showProducts (Producto a1[MAX], int numprod) {
161     int i, j, cont = 1;                                                                                             //contador
162     Producto aux;                                                                                                   //variable auxiliar
163
164
165     printf ("\n");
166
167     if (numprod > 0) {                                                                                              //condicional que verifica existencia de productos
168         for (i = 0; i < numprod; i++) {
169             for (j = 0; j < numprod; j++) {                                                                         //bucle que recorre los productos
170
171                 if (a1[j].stock > a1[j + 1].stock) {                                                                //condicional que ordena productos
172                     aux.stock = a1[j + 1].stock;
173                     strcpy (aux.nombre, a1[j + 1].nombre);
174                     aux.precio = a1[j + 1].precio;
175                     a1[j + 1].stock = a1[j].stock;
176                     strcpy (a1[j + 1].nombre, a1[j].nombre);
177                     a1[j + 1].precio = a1[j].precio;
178                     a1[j].stock = aux.stock;
179                     strcpy (a1[j].nombre, aux.nombre);
180                     a1[j].precio = aux.precio;
181                 }
182             }
183         }
184
185         for (i = 0; i < numprod; i++) {                                                                             //bucle que recorre los productos
186             printf ("Product #%d:\n", cont);
187             printf ("Name: %s\n", a1[i].nombre);
188             printf ("Stock: %d\n", a1[i].stock);
189             printf ("Price: %.2f euros\n", a1[i].precio);
190             printf ("---\n");
191             cont++;
192         }
193     }
194     else {
195         printf ("There are 0 products in the store\n");
196     }
197
198 }
/***********************************************
*
* @Finalidad: mostrar un producto
* @Parametros: in/out (numero de productos)
*              in: a1 (listado de productos)
* @Retorno: 
*
************************************************/
199
200 void listName (int numprod, Producto a1[MAX]) {
201     int i, flag = 0;                                                                                                //contador y flag
202     char name[30];                                                                                                  //producto introducido
203
204     printf ("\nProduct ball?: ");
205     fgets (name, 30, stdin);
206     fgets (name, 30, stdin);
207     name[strlen(name) - 1] = '\0';
208
209     for (i = 0; i < numprod; i++) {                                                                                 //bucle que recorre los productos
210         if (strcmp(name, a1[i].nombre) == 0) {                                                                      //condicional que verifica producto existente
211             flag = 1;
212             printf ("\nProduct found!\n");
213             printf ("Name: %s\n", a1[i].nombre);
214             printf ("Stock: %d units\n", a1[i].stock);
215             printf ("Price: %.2f euros\n", a1[i].precio);
216         }
217     }
218
219     if (flag == 0) {                                                                                                //condicional que muestra error
220         printf ("\nERROR: Product not found\n");
221     }
222 }
223
224 int main () {
225     int opcion = 0;                                                                                                 //variables de menus
226     int op = 0;
227     FILE *f, *g, *h;                                                                                                //ficheros
228     int numprod = 0;                                                                                                //numero de productos
229     char file1[MAX2], file2[MAX2], file3[MAX2];                                                                     //variables de ficheros
230     Producto a1[MAX];                                                                                               //variable para los productos
231
232     printf ("Welcome!\n");
233
234     do {                                                                                                            //bucle que repite el menu
235         opcion = showMenu (opcion);
236
237         if (opcion == 1) {                                                                                          //condicional para la opcion 1
238
239             printf ("\n1. Supplier 1 | 2. Supplier 2 | 3. Supplier 3\n");
240             printf ("Choose one to load from: ");
241             scanf ("%d", &op);
242
243             switch (op) {                                                                                           //sentencia alternativa para menu
244
245                 case 1:
246
247                     printf ("\nType the name of the file (without '.txt'): ");
248                     scanf ("%s", file1);
249                     strcat (file1, ".txt");
250
251                     f = fopen (file1, "r");
252
253                     if (f == NULL) {                                                                                //condicional para apertura de fichero
254                         printf ("\nERROR: Can't open file '%s.txt'\n", file1);
255                     }
256                     else {
257                         numprod = loadFile1 (f, a1, numprod);
258                     }
259
260                         break;
261
262                 case 2:
263
264                     printf ("\nType the name of the file (without '.txt'): ");
265                     scanf ("%s", file2);
266                     strcat (file2, ".txt");
267
268                     g = fopen (file2, "r");
269
270                     if (g == NULL) {                                                                                //condicional para apertura de fichero
271                         printf ("\nERROR: Can't open file '%s.txt'\n", file2);
272                     }
273                     else {
274                         numprod = loadFile2 (g, a1, numprod);
275                     }
276
277                         break;
278
279                 case 3:
280
281                     printf ("\nType the name of the file (without '.bin'): ");
282                     scanf ("%s", file3);
283                     strcat (file3, ".bin");
284
285                     h = fopen (file3, "rb");
286
287                     if (h == NULL) {                                                                                //condcional para apertura de fichero
288                         printf ("\nERROR: Can't open file '%s.bin'\n", file3);
289                     }
290                     else {
291                         numprod = loadFile3 (h, a1, numprod);
292                     }
293
294                         break;
295             }
296         }
297
298         if (opcion == 2){                                                                                           //condicional para opcion 2
299             showProducts (a1, numprod);
300         }
301
302         if (opcion == 3) {                                                                                          //condicional para opcion 3
303             listName(numprod, a1);
304         }
305
306         if (opcion == 4) {                                                                                          //condicional para opcion 4
307             printf ("\nBye");
308         }
309
310     } while (opcion != 4);
311
312     return 0;
313 }



