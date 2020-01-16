<script type="text/javascript">

    $(".qgc").click(function() {
    console.log("Button Clicked!");
    var token = $(this).data("token");
    $.ajax({
        headers: {
        'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content'),
        },
        type:'GET',
        url: '/qgc',
        data: {
            "_method": 'GET',
            '_token': "<?php echo csrf_token() ?>",
        },
        success:function(data) {
            console.log(data);
        }
    });
    });

    $(".start_vm").click(function() {
        
        var id = this.id;
        console.log("/start_vm/"+id);
        var token = $(this).data("token");
        
            $.ajax({
                headers:{
                            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content'),
                        },
                type:'GET',
                url:'/start_vm/'+id,
                success:function(data) {
                    console.log(data);
                }
        }); 
    });
</script>
