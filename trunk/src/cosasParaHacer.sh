# Muestra la lista de cosas para hacer.
# Cuando quieren marcar algo relevante o que tiene algun hardcodeo
# le ponene TODO y aca se va a mostrar para no olvidarnos.
echo "Lista de cosas para hacer:";
fgrep 'TODO' -r -n *;
