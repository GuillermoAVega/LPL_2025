#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/includes.h"
#include <sys/types.h>
#include <sys/stat.h>

const char *menuListados[] = {"Clientes", "Productos", "Medios de pago mas usados", "Productos mas pedidos"};

