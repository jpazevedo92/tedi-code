<div class="col-md-10"> 
    <table style="width:100%">
        <thead>
            <tr>
                <th>In Intf.</th>
                <th>In Label</th>
                <th>Out Intf.</th>
                <th>Out Label</th>
            </tr>
        </thead>
        <div class="form-group">
            <tbody class="table_body">
                @if(isset($uav))
                <tr>
                <td class="col-sm-3">x</td> 
                <td class="col-sm-3">x</td>
                <td class="col-sm-3">x</td>
                <td class="col-sm-3">x</td>
                </tr>
                @else
                <tr class="spacer table_row" id="table_row_main">
                    <td class="col-sm-3">
                        <select name="in_if[]" form="uav" class="form-control sel-status">
                            <option value="0">Select one option</option>
                            @foreach(App\Network::all() as $network)
                                <option value="{{$network->id}}">{{$network->if_name}}</option>
                            @endforeach
                            <option value="#">Other</option>
                        </select>
                    </td>
                    <td class="col-sm-3">
                        <select name="in_label[]" form="uav" class="form-control sel-status">
                            <option value="0">Select one option</option>
                            @foreach(App\MplsTag::all() as $mlps_tag)
                                <option value="{{$mlps_tag->id}}">{{$mlps_tag->tag}}</option>
                            @endforeach
                            <option value="#">Other</option>
                        </select>
                    </td> 
                    <td class="col-sm-3">
                        <select name="out_if[]" form="uav" class="form-control sel-status">
                            <option value="0">Select one option</option>
                            @foreach(App\Network::all() as $network)
                                <option value="{{$network->id}}">{{$network->if_name}}</option>
                            @endforeach
                            <option value="#">Other</option>
                        </select>
                    </td> 
                    <td class="col-sm-3">
                        <select id="out_label" name="out_label[]" form="uav" class="form-control sel-status">
                            <option value="0">Select one option</option>
                            @foreach(App\MplsTag::all() as $mlps_tag)
                                <option value="{{$mlps_tag->id}}">{{$mlps_tag->tag}}</option>
                            @endforeach
                            <option value="#">Other</option>
                        </select>
                        <label style="display:none;">Enter your Name
                        <input>
                        </label>
                    </td>  
                </tr>
                @endif
            </tbody>
            
        </div>
    </table>
</div>
<div class="col-md-2">
    <button type="button" class="btn btn-success add_row"><i class="fa fa-plus-square" aria-hidden="true"></i></button>
</div>

    