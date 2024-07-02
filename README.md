INTRO--------------------------------------------------------------------------

    Empezemos por gerarquia de la minishell. 
    
    Primero van las comillas, segundo las pipes '|',
    
    despues redirecciones '<' o '>' y '<<' o '>>', por ultimo ya el comando y
    
    sus posibles argumentos.

        COMILLAS --> PIPES --> REDIRECCIONES --> COMANDO

1st----------------------------------------------------------------------------

                            <<< COMILLAS >>>

    No interpretar comillas sin cerrar, si son tontos y ponen tres comillas,
        
        Ejemplo: blablabla "holaaaa"bhsbdjh"jbakj

    Solo interpretaremos las comillas que tengan otra despues, en resumen,
    
    que haya una cantidad comillas pares, si no hay dos opciones:

        - Hacer como si nada e interprtarlo como un char normal.

        - Salida de error y que tengan que cerrar las comillas si las ponen.

    Voto por la segunda, mas facil. :D

2nd----------------------------------------------------------------------------

    Gerarquia dentro de comillaaaaaaaaas. >:|

    Las comillas son un coñazo, ya que puede aver comillas simples dentro de 
    
    dobles y dobles dentro de simples,

        Ejemplos:

            - "Holaaaaa 'a' Adios"

            - 'Holaaaaa "a" Adios'

    El primero que salga gana, con esto aprendemos que el ultimo en llegar es 
    
    gei.

3rd----------------------------------------------------------------------------

    Mecanicas de comillas.

    Veamos, depende de el uso de las comillas, pueden salir cosas

    muy turbias.

        Ejemplos:

            - "blablabla" --> blablabla (persona normal)

            - bla"bla"bla --> blablabla (psiopata)

            - bla""blabla --> blablabla (estupido)

            - blabla" bla" --> blabla bla (inglaterra)

    No es muy chungo, pero toca los cojones.

1st----------------------------------------------------------------------------

                            <<< PIPES >>>

    En si, las pipes son lo mas importante en la gerarquia, pero ya que dentro
    
    de unas comillas se puede encontrar una pipe, debemos tener cuidado de no

    interpretarla.

    Aqui empezaremo a explicar que es la tokenizacion, tu diras, que chucha

    madre es eso? Pues como tampoco se explicarlo muy bien, sera mas facil

    verlo con ejemplos.

2nd----------------------------------------------------------------------------

    Tenemos el siguiente comando: "cat texto1.txt > texto2.txt"

    La tokenizacion se basa en interpretar este comando y guardar la

    informacion en una estructura como esta:

        typedef struct s_tokens
        {
            char		**command;
            char		*path;
            int			infile;
            int			outfile;
            s_tokens	*next;
        }	t_tokens;

    command = {"cat", "texto1.txt", NULL}; -> El comando con sus argumentos.

    path = "/usr/bin/cat"; -> La direccion del binario del comando.

    infile = STD_IN; -> El infile y el outfile son para la hora de ejecutar.

    outfile = texto2.txt; -> Por la redireccion el STD_OUT se ha cambiado.

    next = NULL; -> Apunta al proximo token en caso de aver alguna pipe '|'.


