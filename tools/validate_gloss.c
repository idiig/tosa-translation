#include <jansson.h>
#include <stdio.h>

void validate_paragraphs(json_t *paragraphs) {
  if (!json_is_array(paragraphs)) {
    printf("No 'paragraph' array found.\n");
    return;
  }

  size_t i;
  json_t *p;
  json_array_foreach(paragraphs, i, p) {
    json_t *gloss = json_object_get(p, "phrase-gloss");
    if (!gloss)
      printf("[!] paragraph id=%zu missing 'phrase-gloss'\n", i);
    else if (!json_is_array(gloss))
      printf("[!] paragraph id=%zu 'phrase-gloss' not array\n", i);
  }
}

int main(void) {
  json_t *root, *entry, *paragraphs;
  json_error_t error;

  root = json_load_file("tosa.json", 0, &error);
  if (!root) {
    fprintf(stderr, "JSON parse error on line %d: %s\n", error.line,
            error.text);
    return 1;
  }

  /* ★ここが重要：最上位が配列の場合 */
  if (json_is_array(root)) {
    size_t i;
    json_array_foreach(root, i, entry) {
      paragraphs = json_object_get(entry, "paragraph");
      if (paragraphs)
        validate_paragraphs(paragraphs);
      else
        printf("[!] entry %zu has no 'paragraph'\n", i);
    }
  } else if (json_is_object(root)) {
    paragraphs = json_object_get(root, "paragraph");
    if (paragraphs)
      validate_paragraphs(paragraphs);
    else
      printf("[!] root has no 'paragraph'\n");
  } else {
    printf("[!] Unexpected JSON structure.\n");
  }

  json_decref(root);
  return 0;
}
