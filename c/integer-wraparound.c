// Marco Ivaldi <raptor@0xdeadbeef.info>

#include <stdio.h>
#include <stdlib.h>

void bad1()
{
	img_t table_ptr;
	int num_imgs;

	// ...

	num_imgs = get_num_imgs();
	// ruleid: raptor-integer-wraparound
	table_ptr = (img_t*)malloc(sizeof(img_t)*num_imgs);

	// ...
}

// https://vulncat.fortify.com/
void bad2()
{
	int nresp = packet_get_int();

	if (nresp > 0) {
		// ruleid: raptor-integer-wraparound
		response = malloc(nresp*sizeof(char*));
		for (int i = 0; i < nresp; i++) 
			response[i] = packet_get_string(NULL);
	}
}

u_char *make_table(unsigned int width, unsigned int height, u_char *init_row)
{
	unsigned int n;
	int i;
	u_char *buf;

	n = width * height;

	// ruleid: raptor-integer-wraparound
	buf = (char *)malloc(n); 
	if (!buf)
		return NULL;
   	for (i = 0; i < height; i++)
		memcpy(&buf[i*width], init_row, width);

	return buf; 
}

// http://www.phrack.org/issues/60/10.html#article
int myfunction(int *array, int len){
        int *myarray, i;

	// ruleid: raptor-integer-wraparound
        myarray = malloc(len * sizeof(int));
        if(myarray == NULL){
            return -1;
        }

        for(i = 0; i < len; i++){
            myarray[i] = array[i];
        }

        return myarray;
}

static int
set_cursor(struct tfb_softc *sc, struct wsdisplay_cursor *p) 
{
	u_int v, index = 0, count = 0, icount = 0; 
	uint8_t r[2], g[2], b[2], image[512], mask[512]; 
	int error, s;
          
	v = p->which;
	if (v & WSDISPLAY_CURSOR_DOCMAP) {
		index = p->cmap.index; // p->cmap.index is u_int 
		count = p->cmap.count; // p->cmap.count is u_int 
		// ruleid: raptor-integer-wraparound
		if (index >= 2 || (index + count) > 2)
			return (EINVAL);
    error = copyin(p->cmap.red, &r[index], count);
	}
}

void **ht_get_all(ht_t self, int want_key) {
  // ruleid: raptor-integer-wraparound
  void **ret = (void **)calloc(self->num_keys+1, sizeof(void *));
  if (ret) {
    void **tail = ret;
    size_t i;
    for (i = 0; i < self->num_buckets; i++) {
      ht_entry_t curr;
      for (curr = self->buckets[i]; curr; curr = curr->next) {
        *tail++ = (want_key ? curr->key : curr->value);
      }
    }
  }
  return ret;
}

dl_status dl_start(dl_t self) 
{
  // ...
  plist_t dict = plist_new_dict();
  // ...
  char *xml = NULL;
  uint32_t xml_length = 0;
  plist_to_xml(dict, &xml, &xml_length);
  plist_free(dict);

  size_t length = 16 + xml_length;
  // ruleid: raptor-integer-wraparound
  char *packet = (char *)calloc(length, sizeof(char));
  if (!packet) {
    return DL_ERROR;
  }

  // ...
}

int main() 
{
	printf("Hello, World!");
	return 0;
}
