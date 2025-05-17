#!/usr/bin/env bash

# your 42 intra username and email:
USER="ducnguye"
EMAIL="ducnguye@student.42berlin.de"

# loop over every .c/.h
find . -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
  # remove old header (if present)
  sed -i '/\/\* \*\{74\} \*\//,/\/\* \*\{74\} \*\//d' "$file"

  # grab current timestamp
  NOW="$(date +"%Y/%m/%d %H:%M:%S")"

  # build new header and write it + the old content back
  {
    printf '/* ************************************************************************** */\n'
    printf '/*                                                                            */\n'
    printf '/*                                                        :::      ::::::::   */\n'
    printf '/*   %-46s:+:      :+:    :+:   */\n' "$(basename "$file")"
    printf '/*                                                    +:+ +:+         +:+     */\n'
    printf '/*   By: %s <%s> +#+  +:+       +#+        */\n' "$USER" "$EMAIL"
    printf '/*                                                +#+#+#+#+#+   +#+           */\n'
    printf '/*   Created: %s by %-12s+#+    #+#             */\n' "$NOW" "$USER"
    printf '/*   Updated: %s by %-12s###   ########.fr       */\n' "$NOW" "$USER"
    printf '/*                                                                            */\n'
    printf '/* ************************************************************************** */\n\n'
    cat "$file"
  } > "$file.tmp" && mv "$file.tmp" "$file"

  echo "Processed: $file"
done

echo "All done!"
