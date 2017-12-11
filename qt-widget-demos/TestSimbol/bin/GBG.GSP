<?xml version="1.0" encoding="utf-8" ?>
<GSPModel GSPModelNode="True" DataFormatVersion="2.5.12" BizVersion="" xmlns:a="attribute" xmlns:c="collection" xmlns:o="object">
    <a:Version>2.5.12</a:Version>
    <a:Name>Cluster</a:Name>
    <a:Mode>2</a:Mode>
    <c:Databases>
        <o:Database>
            <a:Name>DB</a:Name>
            <c:Tables>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>FBFX</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>FBFXID</a:FieldName>
                                <a:DisplayName>分部分项ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>PID</a:FieldName>
                                <a:DisplayName>PID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                                <a:LookupKind>1</a:LookupKind>
                                <a:LookupTableName>FBFX</a:LookupTableName>
                                <a:LookupResult>FBFXID</a:LookupResult>
                                <a:LookupDescription>MC</a:LookupDescription>
                                <a:Aggregate>True</a:Aggregate>
                                <a:MasterTableName>FBFX</a:MasterTableName>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>RGHJ</a:FieldName>
                                <a:DisplayName>人工费合计</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItem.RGHJ[FBFXID = ?FBFX.FBFXID].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>CLHJ</a:FieldName>
                                <a:DisplayName>材料费合计</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItem.CLHJ[FBFXID = ?FBFX.FBFXID].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>JXHJ</a:FieldName>
                                <a:DisplayName>机械费合计</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItem.JXHJ[FBFXID = ?FBFX.FBFXID].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>JE</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>FBFX.JE[PID=?FBFXID].Sum + RGHJ + CLHJ + JXHJ</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>MC</a:FieldName>
                                <a:DisplayName>分部分项名称</a:DisplayName>
                                <a:StrLength>255</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>CJSJ</a:FieldName>
                                <a:DisplayName>创建时间</a:DisplayName>
                                <a:DataType>9</a:DataType>
                                <a:DefaultExpr>now()</a:DefaultExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="3">
                                <a:FieldName>FBLX</a:FieldName>
                                <a:DisplayName>分部类型</a:DisplayName>
                                <a:DataType>2</a:DataType>
                                <a:EnumNames>0=系统分部|1=自定义分部</a:EnumNames>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <a:CompressData>True</a:CompressData>
                        <o:Records>eAH7////fx5WJoYVzAwMXAwMDIwMxoIMDJxAFk5w9syZM0+anjkwsACVWCcE+z+N5a6C6rABmQEyAR/QjOk/ZNv6yIGBHajKhoHBz47hV7hDxYsJbEEM8pUFdpe9njhA9F8VAKkAmQnXA5FAJuFSION2+T2NlQ//XL4zFeQqNOMaiHHdOveHVSLfqmGu6wG6TqziczkW4+4CXacANnNJgS3XdfNiB4SzREDG1CQ6MMCNA4UWDoM2wd3FdX1xge3hrQ4MxiBwdQGSiWA7dPc5MPABDbJh4AS663vu3UD58FPBi6Z4V0PYWFz5HehKTYTD8LB4gXIXJ8bFtKR/8zMLivE/Ffxi6vSqzuijHViMZQdGMnHGsgKNrck0CE+ajsUYdUKpDe5eUPgd7SiYicUQGyECSRZuCCiJpHa4BgZEvys7FRyQPjMVkUQYgXIAhEuVCA==                        </o:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>NormItem</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>NormItemID</a:FieldName>
                                <a:DisplayName>子目ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>FBFXID</a:FieldName>
                                <a:DisplayName>分部分项ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                                <a:LookupKind>1</a:LookupKind>
                                <a:LookupTableName>FBFX</a:LookupTableName>
                                <a:LookupResult>FBFXID</a:LookupResult>
                                <a:LookupDescription>MC</a:LookupDescription>
                                <a:MasterTableName>FBFX</a:MasterTableName>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>LB</a:FieldName>
                                <a:DisplayName>类别</a:DisplayName>
                                <a:DataType>4</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>BH</a:FieldName>
                                <a:DisplayName>编号</a:DisplayName>
                                <a:StrLength>32</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>MC</a:FieldName>
                                <a:DisplayName>名称</a:DisplayName>
                                <a:StrLength>255</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>DW</a:FieldName>
                                <a:DisplayName>单位</a:DisplayName>
                                <a:StrLength>16</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>Factor</a:FieldName>
                                <a:DisplayName>Factor</a:DisplayName>
                                <a:DataType>7</a:DataType>
                                <a:DefaultExpr>1</a:DefaultExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="4">
                                <a:FieldName>BDS</a:FieldName>
                                <a:DisplayName>工程量表达式</a:DisplayName>
                                <a:DataType>7</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>GCL</a:FieldName>
                                <a:DisplayName>工程量</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>3</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>BDS/Factor</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>RGDJ</a:FieldName>
                                <a:DisplayName>人工单价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItemUsage.JE[(NormItemID = ?NormItem.NormItemID) and (Resource.LB = 1)].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>CLDJ</a:FieldName>
                                <a:DisplayName>材料单价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItemUsage.JE[(NormItemID = ?NormItem.NormItemID) and (Resource.LB = 2)].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>JXDJ</a:FieldName>
                                <a:DisplayName>机械单价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItemUsage.JE[(NormItemID = ?NormItem.NormItemID) and (Resource.LB = 3)].Sum</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>DJ</a:FieldName>
                                <a:DisplayName>单价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>RGDJ + CLDJ + JXDJ</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>HJ</a:FieldName>
                                <a:DisplayName>合价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>DJ * GCL</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>LB1</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>LB2</a:FieldName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>RGHJ</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>RGDJ * GCL</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>CLHJ</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>CLDJ * GCL</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>JXHJ</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>JXDJ * GCL</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>Main</a:FieldName>
                                <a:DataType>1</a:DataType>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <a:CompressData>True</a:CompressData>
                        <o:Records>eAH7////fx5WJoYVzAwMLAwMDIwMtlxA6qoAkOBhAAoyGDLoMpgxMPADmbv8nsaKJc/P+ZupwSCW/DFXI1yTQYHBhCGX4alfayADK1i1AYMBUMAYyAaDSAcGLx4m7eNGqxw4gALGQGgKxHpAbMFgCTSeY41M1BEHB4aY/kNfNSonOEC0oZBwqR1yra8DnR86cHIywJgoCiEcRgZ7JD+AfAXygyHINhCnOK4k1SrcIBzFvUYwc4DuTXh6Qem21Hywe0G6LIE+0mMwB5pgAgyZipdqhi+MHRiWFNhyXddOcIBpRKLhUlzXFxfslVsCci+MiaQMwXQFufcuJMxh7jUC2gd27/xg+XD9yHnRON1bCHTI4hUTHNiBhhgC3WoGhHpAFjDWcp//XvkxSNWBAegQoCobB4SdIE0FtloODNUi69wf/nJxYABSVSLfqkGuBfvAvBhJOUhRVU2iAyeDI8ixm0AED9h9oMA1AlrLwAYU2j1lUfKp4Hth2REhuB0854jChk8Bi8ABbARMCCZAqAfE5qAADgLFbKE5NEFsyXVgmDUTCH6GoTtmRgnEyVd098EC2PbwVgcGYxC4ugChnBMAUSqXwA==                        </o:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>Resource</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>ResID</a:FieldName>
                                <a:DisplayName>材料ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>CLH</a:FieldName>
                                <a:DisplayName>材料号</a:DisplayName>
                                <a:StrLength>32</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>CLM</a:FieldName>
                                <a:DisplayName>材料名</a:DisplayName>
                                <a:StrLength>255</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>DW</a:FieldName>
                                <a:DisplayName>单位</a:DisplayName>
                                <a:StrLength>16</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>LB</a:FieldName>
                                <a:DisplayName>材料类别</a:DisplayName>
                                <a:DataType>4</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>DJ</a:FieldName>
                                <a:DisplayName>单价</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>CLL</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>NormItemUsage.CLL[ResID = ?Resource.ResID].Sum</a:CalcExpr>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <a:CompressData>True</a:CompressData>
                        <o:Records>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                        </o:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>NormItemUsage</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>UsageID</a:FieldName>
                                <a:DisplayName>含量ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>NormItemID</a:FieldName>
                                <a:DisplayName>子目ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                                <a:MasterTableName>NormItem</a:MasterTableName>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="1">
                                <a:FieldName>ResID</a:FieldName>
                                <a:DisplayName>材料ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                                <a:MasterTableName>Resource</a:MasterTableName>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>YSHL</a:FieldName>
                                <a:DisplayName>原始含量</a:DisplayName>
                                <a:DataType>7</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>HLXS1</a:FieldName>
                                <a:DisplayName>含量系数1</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>4</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>HLXS2</a:FieldName>
                                <a:DisplayName>含量系数2</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>4</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>JE</a:FieldName>
                                <a:DisplayName>金额</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>HL * Resource.DJ</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>CLL</a:FieldName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>3</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>HL*NormItem.GCL</a:CalcExpr>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>HL</a:FieldName>
                                <a:DisplayName>含量</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>4</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>YSHL*HLXS1*HLXS2</a:CalcExpr>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <a:CompressData>True</a:CompressData>
                        <o:Records>eAH7////fx5WJoYVzAwM7AwMDIwMdlxAyhZEgIHIOveHVV88HaDcD/YIRkz/oa8alROgUsazHRjgih1A+u3hhlSDJSShKhmQDVlSYMt1XTvBgeHgqYWu2zbHOzDAFTuB9DvCDUkDA3VshoBdsiXXgeHL3ysVL1UKHRjgip3hhqQDTWNY5Lrt898rb5B8ARJlADlp1kwg+BnmwGC55UTZPnlTB4RiF7ghTSDFmmD7/mAzBCQNBt05z3+vXOjigFDsBjLEFe6dHXKtrwN3fMNmyPXFoECxcWDweFgFDDk9Bwa4Yne4IRNB1gCVAdVqOYDYQIAcsHApsN6aRAe4YgBTnoCE                        </o:Records>
                    </o:TableData>
                </o:Table>
                <o:Table TableKind="0">
                    <o:TableSchema>
                        <a:Name>FYWJ</a:Name>
                        <a:CommandEnable>True</a:CommandEnable>
                        <a:RowRefEnable>True</a:RowRefEnable>
                        <c:FieldSchemas>
                            <o:FieldSchema FieldKind="0">
                                <a:FieldName>ID</a:FieldName>
                                <a:DisplayName>ID</a:DisplayName>
                                <a:DataType>2</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>XH</a:FieldName>
                                <a:DisplayName>序号</a:DisplayName>
                                <a:StrLength>16</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>FYMC</a:FieldName>
                                <a:DisplayName>费用名称</a:DisplayName>
                                <a:StrLength>255</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="4">
                                <a:FieldName>QFJS</a:FieldName>
                                <a:DisplayName>取费基数</a:DisplayName>
                                <a:DataType>7</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>QFSM</a:FieldName>
                                <a:DisplayName>取费说明</a:DisplayName>
                                <a:StrLength>255</a:StrLength>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="2">
                                <a:FieldName>FL</a:FieldName>
                                <a:DisplayName>费率</a:DisplayName>
                                <a:DataType>7</a:DataType>
                            </o:FieldSchema>
                            <o:FieldSchema FieldKind="5">
                                <a:FieldName>FYJE</a:FieldName>
                                <a:DisplayName>费用金额</a:DisplayName>
                                <a:DataType>8</a:DataType>
                                <a:Precision>2</a:Precision>
                                <a:IgnoreZero>True</a:IgnoreZero>
                                <a:CalcExpr>QFJS * FL</a:CalcExpr>
                            </o:FieldSchema>
                        </c:FieldSchemas>
                    </o:TableSchema>
                    <o:TableData>
                        <a:CompressData>True</a:CompressData>
                        <o:Records>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                        </o:Records>
                    </o:TableData>
                </o:Table>
            </c:Tables>
        </o:Database>
    </c:Databases>
</GSPModel>
