#!/bin/bash

YESTERDAY=$(date -d "yesterday" +"%Y/%m/%d")
TODAY=$(date +"%Y/%m/%d")
TIME="12:00:00"
NAME="ducnguye"
EMAIL="ducnguye@student.42berlin.de"

HEADER_TEMPLATE='/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   %s%s */
/*                                                    +:+ +:+         +:+     */
/*   By: %s <%s>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: %s %s by %s          #+#    #+#             */
/*   Updated: %s %s by %s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */'

for file in $(find . -type f \( -name "*.c" -o -name "*.h" \)); do
	filename=$(basename "$file")
	spaces=$(printf "%*s" $((50 - ${#filename})) "")
	header=$(printf "$HEADER_TEMPLATE" "$filename" "$spaces" "$NAME" "$EMAIL" "$YESTERDAY" "$TIME" "$NAME" "$TODAY" "$TIME" "$NAME")
	# Remove old header (first 11 lines assumed), then prepend new one
	tail -n +12 "$file" > tmpfile && echo "$header" > "$file" && cat tmpfile >> "$file" && rm tmpfile
done
