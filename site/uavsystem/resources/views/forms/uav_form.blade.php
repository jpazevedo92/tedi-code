<form class="form-horizontal" action="{{isset($uav) ? '/uavs/'.$uav->id : '/uavs'}}" method="POST" enctype = "multipart/form-data">
    {{ isset($uav) ? method_field('PATCH') : ''}}
    {{ csrf_field() }}
    <div class="form-group">
        <label class="control-label col-sm-1" for="name">Name:</label>
        <div class="col-sm-5">
            <input type="text" class="form-control" id="name" placeholder="Enter UAV name" name="name" value="{{ isset($uav) ?  $uav->name : null }}">
        </div>
        <label class="control-label col-sm-1" for="local_ip">Local IP:</label>
        <div class="col-sm-5">
            <input type="text" class="form-control" id="local_ip" placeholder="Enter Local IP" name="local_ip" value="{{ isset($uav) ?  $uav->local_ip : null }}">
        </div>
    </div>
    <div class="form-group">
        <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default">{{ isset($uav) ?  'Update' : 'Submit' }}</button>
        </div>
    </div> 
</form>