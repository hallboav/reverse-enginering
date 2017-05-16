# readv-writev & ptrace

Memory editing.

### Descrição

No *SO* Windows podemos ler e alterar a memória de outro processo usando as funções ``ReadProcessMemory`` e ``WriteProcessMemory`` que são declaradas na biblioteca ``winbase.h``.

``readv-writev`` e ``ptrace`` são duas soluções econtradas para obter o *mesmo* comportamento nos sistemas Linux.

### Modo de usar

Primeiro devemos compilar o binário alvo.

#### target

```shell
gcc target.c -o target
./target
```

Deixe-o em execução e inicie outro terminal.

#### readv-writev

```shell
gcc readv-writev.c -o readv-writev
sudo ./readv-writev 14344
```

#### ptrace

Nota: ``ptrace`` envia o sinal ``SIGSTOP`` e espera o *tracee* parar.

```shell
gcc ptrace.c -o ptrace
sudo ./ptrace 14344

```

Onde 14344 é o *PID*.

### Obtendo endereço de memória

Você pode usar o ``gdb`` caso seja necessário atualizar o endereço de memória.

Este pode ser visto em comentário (prefixado pelo caractere ``#``) à direita do terminal.

```shell
gdb target
set disassembly-flavor intel # opcional
disassemble main
```
