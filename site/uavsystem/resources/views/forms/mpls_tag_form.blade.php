<form class="form-horizontal" action="{{isset($mpls_tag) ? '/mpls_tags/'.$mpls_tag->id : '/mpls_tags'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($mpls_tag) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}
    <div class="form-group">
        <label class="control-label col-sm-1" for="Tag">Tag:</label>
        <div class="col-sm-5">
            <input type="text" class="form-control" id="tag" placeholder="Enter MPLS Tag" name="tag" value="{{ isset($mpls_tag) ?  $mpls_tag->tag : null }}">
        </div>
    </div>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($mpls_tag) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>