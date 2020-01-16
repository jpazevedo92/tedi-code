<script type="text/javascript">

$(".del_route").click(function() {
    id=this.id;
    console.log("/uav_routes/"+id);
    var token = $(this).data("token");

    $.ajax({
               type:'DELETE',
               url:'/uav_routes/'+id,
               data: {
                '_token': "<?php echo csrf_token() ?>",
                "id": id,
                "_method": 'DELETE',
               },
               success:function(data) {
                    $('.tr_'+id).remove();
                  console.log(data);
               }
            });
});
</script>