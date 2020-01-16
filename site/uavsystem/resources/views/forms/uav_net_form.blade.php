<div class="col-md-10"> 
    <table style="width:100%" id="routes_table">
        <thead>
            <tr>
                <th>IN Interface</th>
                <th>IN Label</th>
                <th>OUT Interface</th>
                <th>OUT Label</th>
                @if(isset($routes))
                    <th>Options</th>
                @endif
            </tr>
        </thead>
        <div class="form-group">
            <tbody class="table_body">
                @if(isset($uav))
                    @foreach($routes as $route)
                    <tr class="spacer table_row tr_{{$route->id}}" id="table_row_main">
                        <td class="col-sm-2">
                            <select name="in_if[]" form="uav" class="select2 form-control js-example-theme-multiple" style="width: 75%">
                                <option value="0">Select one option</option>
                                @foreach(App\Device::all() as $device)
                                    <option value="{{$device->id}}" @if(isset($route) && $route->in_if_id == $device->id) selected @endif>{{$device->name}}</option>
                                @endforeach
                            </select>
                        </td>
                    <td class="col-sm-2">
                        <select name="in_label[]" form="uav" class="select2 form-control js-example-theme-multiple" style="width: 75%">
                            <option value="0">Select one option</option>
                            @foreach(App\MplsTag::all() as $mpls_tag)
                                <option value="{{$mpls_tag->id}}" @if ( isset($route) && $route->in_tag_id == $mpls_tag->id ) selected @endif> {{isset($route) && $route->in_tag_id == null ? x: $mpls_tag->tag}}</option>
                            @endforeach
                        </select>
                    </td> 
                    <td class="col-sm-2">
                        <select name="out_if[]" form="uav" class="select2 form-control js-example-theme-multiple"  style="width: 75%">
                            <option value="0">Select one option</option>
                            @foreach(App\Device::all() as $device)
                                <option value="{{$device->id}}" @if(isset($route) && $route->out_if_id == $device->id) selected @endif>{{$device->name}}</option>
                            @endforeach
                        </select>
                        </select>
                    </td> 
                    <td class="col-sm-2">
                        <select id="out_label" name="out_label[]" form="uav" class=" select2 form-control js-example-theme-multiple" style="width: 75%">
                            <option value="0">Select one option</option>
                            @foreach(App\MplsTag::all() as $mpls_tag)
                                <option value="{{$mpls_tag->id}}"  @if ( isset($route) && $route->out_tag_id == $mpls_tag->id ) selected @endif>{{$mpls_tag->tag}}</option>
                            @endforeach
                        </select>
                    </td>
                    <td class="col-sm-1">
                        <button type="button" class="btn btn-danger del_route" id="{{$route->id}}"><i class="fa fa-trash"></i></a>
                    </td> 
                </tr>
                    @endforeach
                @else
                <!-- multiple="multiple" -->
                <tr class="spacer table_row" id="table_row_main">
                    <td class="col-sm-3">
                        <select name="in_if[]" form="uav" class="select2 form-control js-example-theme-multiple" style="width: 75%">
                        <!--                             <option value="0">Select one option</option> -->
                            @foreach(App\Device::all() as $device)
                                <option value="{{$device->id}}">{{$device->name}}</option>
                            @endforeach
                        </select>
                    </td>
                    <td class="col-sm-3">
                        <select name="in_label[]" form="uav" class="select2 form-control js-example-theme-multiple" style="width: 75%">
<!--                             <option value="0">Select one option</option> -->
                            @foreach(App\MplsTag::all() as $mlps_tag)
                                <option value="{{$mlps_tag->id}}">{{$mlps_tag->tag}}</option>
                            @endforeach
                        </select>
                    </td>
                    <td class="col-sm-3">
                        <select name="out_if[]" form="uav" class="select2 form-control js-example-theme-multiple"  style="width: 75%">
                            <!-- <option value="0">Select one option</option> -->
                            @foreach(App\Device::all() as $device)
                                <option value="{{$device->id}}">{{$device->name}}</option>
                            @endforeach
                        </select>
                    </td>
                    <td class="col-sm-3">
                        <select id="out_label" name="out_label[]" form="uav" class="select2 form-control js-example-theme-multiple" style="width: 75%">
                            <!-- <option value="0">Select one option</option> -->
                            @foreach(App\MplsTag::all() as $mlps_tag)
                                <option value="{{$mlps_tag->id}}">{{$mlps_tag->tag}}</option>
                            @endforeach
                        </select>
                    </td>
                </tr>
                @endif
            </tbody>
            
        </div>
    </table>
</div>
<div class="col-md-2">
    <table>
        <thead>
            <tr style="border: 5px solid white;">
                <th>Operations</th>
            </tr>
        <thead>
        <tbody>
            <tr style="border: 5px solid white;">
                <td><button type="button" class="btn btn-success add_row"><i class="fa fa-plus-square" aria-hidden="true"></i> Add Row</button></td>
            </tr>
            @if(isset($uav))
                <tr style="border: 5px solid white;">
                    <td><a href="/download_cfg/{{$uav->id}}" class="btn btn-info"><i class="fa fa-download" aria-hidden="true"></i> Download </button></a></td>
                    <!-- <td><button type="button" id="{{ $uav->id }}" class="btn btn-info download_cfg"><i class="fa fa-download" aria-hidden="true"></i> Download </button></td> -->
                </tr>
            @endif
        </tbody>
    </table>
    
</div>

    