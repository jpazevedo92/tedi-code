<script type="text/javascript">
    $(".table_row").css({"border" : "5px solid white"});
    $(document).on('click', '.add_row', function() {
        
        $("#table_row_main" ).clone().attr("id", "table_row").appendTo( ".table_body" );
        console.log('add row to the table.')
});
</script>