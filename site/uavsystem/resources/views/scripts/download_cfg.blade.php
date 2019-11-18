<script type="text/javascript">
    $(document).on('click', '.download_cfg', function() {
        var id = {{$uav->id}}
        var token = $(this).data("token");
        $.ajax({
            headers:{
                'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content'),
            },
            type:'GET',
            url:'/download_cfg/'+id,
            success:function(data) {
                console.log(data);
            }
        });
    });
</script>