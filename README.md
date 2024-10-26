
<h1 align="center">
  libconfusables
  <br>
</h1>

<h4 align="center">A small C library to remove unicode confusables.</h4>


## How To Use

```c
const char *test_str = "𝐓𝐡𝖎𝑠 𝙞𝘴 𝒂 𝕥𝔢𝔰𝓽 𝓼𝕥𝕣𝓲𝓷𝓰 𝖜𝖎𝘁𝖍 𝓶𝓪𝓷𝔂 𝕔𝔬𝖓𝖋𝕦𝓼𝓪𝖇𝔩𝓮𝕤.";
char *result = replace_confusables(test_str);

if (result) {
    printf("Original: %s\n", test_str);
    printf("Processed: %s\n", result);
} else {
    printf("Something failed.\n");
}

return 0;
```

## License

* The library itself underlies the MIT LICENSE.

---
