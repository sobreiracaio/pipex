/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:32:13 by admin             #+#    #+#             */
/*   Updated: 2023/05/06 10:27:26 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



unsigned int countwords(const char *str, char c)
{
    int counter; // Contador para armazenar o número de palavras encontradas
    int marker; // Marcador para acompanhar se está dentro de uma palavra ou não

    counter = 0; // Inicializa o contador como 0
    marker = 0; // Inicializa o marcador como 0

    while (*str) // Loop para percorrer a string fornecida
    {
        if (*str != c && marker == 0) // Verifica se o caractere atual não é o delimitador e se não está dentro de uma palavra
        {
            marker = 1; // Define o marcador como 1, indicando que está dentro de uma palavra
            counter++; // Incrementa o contador para contar a palavra
        }
        else if (*str == c) // Verifica se o caractere atual é o delimitador
        {
            marker = 0; // Define o marcador como 0, indicando que não está dentro de uma palavra
        }
        str++; // Move para o próximo caractere na string
    }

    return (counter); // Retorna o número total de palavras encontradas
}

static char *duplicatewords(const char *str, int start, int end)
{
    char *word; // Ponteiro para armazenar a palavra duplicada
    int i;

    i = 0;
    word = (char *)malloc((end - start + 1) * sizeof(char)); // Aloca memória para a palavra duplicada
    while (start < end) // Loop para copiar os caracteres da palavra original para a palavra duplicada
    {
        word[i++] = str[start++]; // Copia o caractere da posição start para a posição i em word
    }
    word[i] = '\0'; // Adiciona o caractere nulo no final da palavra duplicada

    return (word); // Retorna a palavra duplicada
}

char	**ft_split(char const *s, char c)
{
	unsigned int		i; // Índice para percorrer a string
	unsigned int		j; // Índice para percorrer o array de strings
	int					index; // Índice para a posição inicial de cada palavra
	char				**split; // Ponteiro para o array de strings criado

	i = 0;
	j = 0;
	index = -1; // Define o índice inicial como -1 para indicar que não há palavras sendo lidas
	split = (char **)malloc((countwords(s, c) + 1) * sizeof(char *)); // Aloca memória para o array de strings
	if (!s || !split) // Verifica se houve um erro ao alocar memória
		return (NULL); // Retorna NULL para indicar um erro

	while (i <= ft_strlen(s)) // Loop até o final da string
	{
		if (s[i] != c && index < 0) // Se o caractere não for um delimitador e ainda não estiver lendo uma palavra
			index = i; // Marca a posição inicial da nova palavra
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0) // Se o caractere for um delimitador ou se a string terminar e uma palavra estiver sendo lida
		{
			split[j++] = duplicatewords(s, index, i); // Copia a palavra para o array de strings
			index = -1; // Reinicia o índice inicial para indicar que nenhuma palavra está sendo lida
		}
		i++; // Move para o próximo caractere na string
	}
	split[j] = 0;
	return (split);
}