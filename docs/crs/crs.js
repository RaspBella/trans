import createModule from '../crs.mjs';

(async () => {
  const Module = await createModule();

  function crs(code) {
    const bytes = Module.lengthBytesUTF8(code) + 1;

    const input = Module._malloc(bytes);

    Module.stringToUTF8(code, input, bytes);

    const output = Module._crs(input);

    const result = Module.UTF8ToString(output);

    Module._free(input);

    return result;
  }

  window.crs = crs;
})();
