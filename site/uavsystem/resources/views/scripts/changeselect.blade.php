<script type="text/javascript">
    $('#out_label').on('select2:select', function (e) {
        console.log("Come here")
        /*if($('select option:selected').text() == "Other"){
            $('label').show();*/
     });
     
    }
     $('#out_label')
         .append($("<option></option>")
                    .attr("value",key)
                    .text(value)); 
<\script>