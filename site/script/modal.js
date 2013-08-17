$(function( ) {
  $( "#header-license, #main-license" ).click(function( ) {
      $( "#dialog-confirm" ).dialog({
        resizable: false,
        closeOnEscape: false,
        height:800,
        width: 600,
        modal: true,
        draggable: false,
        dialogClass: "alert",
        buttons: {
          Purchase: function() {
            $( this ).dialog( "close" );
          },
          Cancel: function() {
            $( this ).dialog( "close" );
          }
        }
      });

      return false;
  });
});